linux_check_release(void)
{
  FILE *fp;
  char osl[128];
  char *cmd = strdup("/bin/uname -r");
  int major = 0;
  int minor = 0;
  int revision = 0;

  if (cmd == NULL) {
    printf("ERROR: Unable to allocate memory\n");
    goto done;
  }

  if (flag_html) printf("<P>\n");
  if (flag_debug) printf("DEBUG  : %s\n",cmd);
  fp = popen(cmd,"r");

  if (fp == NULL) {
    perror("popen");
    goto done;
  }

  if (fgets(osl,128,fp) == NULL) {
	printf("WARNING: Cannot determine the kernel number.\n");
	pclose(fp);
	flag_warnings++;
	goto done;
  }
  pclose(fp);

  if (flag_debug) {
	printf("DEBUG  : %s\n",osl);
  }

  major = atoi(strtok(osl, "."));
  minor = atoi(strtok(NULL, "."));
  revision = atoi(strtok(NULL, "-"));

  if (major < 2) {
	printf("ERROR: We support kernel version 2.4.7 and higher.\n\n");
	flag_os_bad = 1;
	goto done;
  } else if (major == 2) {
	if (minor < 4) {
		printf("ERROR: We support kernel version 2.4.7 and higher.\n\n");
		flag_os_bad = 1;
		goto done;
	} else if (minor == 4) {
		if (revision < 7) {
			printf("ERROR: We support kernel version 2.4.7 and higher.\n\n");
			flag_os_bad = 1;
			goto done;
		}
	}
  }
done:
  if (cmd) free(cmd);
}
