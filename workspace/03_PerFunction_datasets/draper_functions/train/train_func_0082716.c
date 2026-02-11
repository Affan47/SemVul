csv_fgets (char *s, int n, FILE *fp)
{
    int i, c1, c = 0;

    for (i=0; i<n-1 && c!=0x0a; i++) {
	c = fgetc(fp);
	if (c == EOF) {
	    if (i == 0) {

		return NULL;
	    } else {
		break;
	    }
	} else if (c == 0x0d) {


	    c = 0x0a;
	    c1 = fgetc(fp);
	    if (c1 != 0x0a) {
		ungetc(c1, fp);
	    }
	}
	s[i] = c;
    }

    s[i] = '\0';

    return s;
}
