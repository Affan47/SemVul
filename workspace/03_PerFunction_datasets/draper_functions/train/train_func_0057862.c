put_one_arg(int type, char *str, char **store, char *prefix, char *string)
#endif
{
    int length = 0;
    long L;

    if (store) {
	switch (type) {
	    case P_STRING:
	    case P_FILE:
	    case P_OLD_FILE:
	    case P_NEW_FILE:
		if (str == NULL) {
			fprintf(stderr, "%s: Missing argument after '%s%s'\n",
				this_program, prefix, string);
			length = 0;
			badargs++;
			}
		else
			length = strlen(*store = str);
		break;
	    case P_CHAR:
		*((char *) store) = *str;
		length = 1;
		break;
	    case P_SHORT:
		L = atol(str);
		*(short *)store = (short) L;
		if (L != *(short *)store) {
		    fprintf(stderr,
	"%s%s parameter '%ld' is not a SHORT INT (truncating to %d)\n",
			    prefix, string, L, *(short *)store);
		    badargs++;
		    }
		length = strlen (str);
		break;
	    case P_INT:
		L = atol(str);
		*(int *)store = (int)L;
		if (L != *(int *)store) {
		    fprintf(stderr,
	"%s%s parameter '%ld' is not an INT (truncating to %d)\n",
			    prefix, string, L, *(int *)store);
		    badargs++;
		    }
		length = strlen (str);
		break;
	    case P_LONG:
		*(long *)store = atol(str);
		length = strlen (str);
		break;
	    case P_FLOAT:
		*((float *) store) = (float) atof(str);
		length = strlen (str);
		break;
	    case P_DOUBLE:
		*((double *) store) = (double) atof(str);
		length = strlen (str);
		break;
	    default:
		fprintf (stderr, "put_one_arg:  bad type '%d'\n", type);
		badargs++;
		break;
	}
    }

    return length;
}
