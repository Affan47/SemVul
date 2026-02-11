index_usage(SgrepData *sgrep) {
    int i;
    sgrep_error(sgrep,"Usage: (sgindex | sgrep -I) [ -");
    for(i=0;index_options[i].opt!=0;i++) {
	if (index_options[i].have_param!=NULL)
	{
	    sgrep_error(sgrep," -%c %s",
		    index_options[i].opt,
		    index_options[i].have_param);
	} else sgrep_error(sgrep,"%c",index_options[i].opt);
    }
    sgrep_error(sgrep," ] [<files...>]\n");
    sgrep_error(sgrep,"sgindex -h for help\n");
}
