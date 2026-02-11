get_string_stdin(char **val, char *prompt, int echo)
{
#define DEFAULT_STRING_LENGTH 16
	int count = 0;
	struct termios saved_settings;
	int length = DEFAULT_STRING_LENGTH;
	char *temp;
	int rc = 0;
	int c;

	printf("%s: ", prompt);
	temp = malloc(length);
	if (!temp) {
		rc = -ENOMEM;
		goto out;
	}
	temp[0] = '\0';
	*val = temp;
	if (!echo) {
		rc = disable_echo(&saved_settings);
		if (rc)
			goto out;
	}
	do {
		if (count == length) {
			temp = malloc(length * 2);
			if (!temp) {
				rc = -ENOMEM;
				goto out;
			}
			memcpy(temp, *val, length);
			memset(*val, 0, length);
			length *= 2;
			free(*val);
			*val = temp;
		}
		if ((c = mygetchar()) != EOF)
			(*val)[count] = c;
		else
			(*val)[count] = '\n';
		count++;
	} while(c != EOF && (*val)[count-1] != '\n');
	(*val)[count - 1] = '\0';
	if (!echo) {
		printf("\n");
		rc = enable_echo(&saved_settings);
	}
	if (count == 1 && c == EOF) {
		free(*val);
		*val = NULL;
		rc = -EIO;
	}
out:
	return rc;
}
