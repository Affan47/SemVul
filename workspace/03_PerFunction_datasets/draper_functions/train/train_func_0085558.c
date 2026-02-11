string_to_list(char* s)
{
    int string_count = 0;
    int in_space = 1;
    char *p;

    for (p = s; *p != '\0'; p++) {
	if (in_space) {
	    if (' ' != *p) {

		string_count++;
		in_space = 0;
	    }
	}
	else if (' ' == *p) {

	    in_space = 1;
	}
    }


    if (string_count > 0) {
	char **return_array = (char **)malloc((string_count+1)*sizeof(char *));
	int index = 0;

	in_space = 1;
	for (p = s; *p != '\0'; p++) {
	    if (in_space) {
		if (' ' != *p) {

		    return_array[index++] = p;
		    in_space = 0;
		}
	    }
	    else if (' ' == *p) {

		in_space = 1;
		*p = '\0';
	    }
	}
	return_array[index] = 0;
	return return_array;
    }
    else return 0;
}
