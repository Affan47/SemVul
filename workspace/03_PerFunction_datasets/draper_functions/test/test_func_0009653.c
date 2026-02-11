display_args_err(char *s, char **a, int err)
{
    char  errstr[256], *errp;
    FILE *fp = err ? stderr : stdout;


    if(err && s){
	snprintf(errp = errstr, sizeof(errstr), "%s: %s", _("Argument Error"), s);
	errstr[sizeof(errstr)-1] = '\0';
    }
    else
      errp = s;

#ifdef	_WINDOWS
    if(errp)
      mswin_messagebox(errp, err);

    if(a && *a){
	os_argsdialog(a);
    }
#else
    if(errp)
      fprintf(fp, "%s\n", errp);

    while(a && *a)
      fprintf(fp, "%s\n", *a++);
#endif
}
