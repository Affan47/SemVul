process_arname (template)
char *template;
{
	int remain, len;
	char *sptr, *dptr;

	sptr=template;
	dptr=proc_arname;

	if(!sflagused)
	  {
	    strcpy(dptr,sptr);
	    return;
	  }

	remain = sizeof(proc_arname)-10;

	for (; remain>=0; sptr++) {
		*dptr = '\0';
		if (*sptr == '%') {
			switch (*++sptr) {
			case 'V':
			  if (remain < 40) break;
			  len = sprintf(dptr,"%u", arvolume);
			  dptr += len;
			  remain -= len;
			  break;
			case 'S':
			  if (remain < 40) break;
			  len = sprintf(dptr,"%llu", (unsigned long long) aruntil);
			  dptr += len;
			  remain -= len;
			  break;
			default:
			  *dptr++ = *sptr;
			  remain--;
			  break;
			}
		}
		else {
			*dptr++ = *sptr;
			remain--;
		}
		if (*sptr == '\0') break;
	}

}
