tmsgl(s) char *s; {
    if (!quiet) {
	if (raw)
	  fprintf(stderr,"%s\r\n",s);
	else
	  fprintf(stderr,"%s\n",s);
    }
}
