help_name2section(char *url, int url_len)
{
    char		name[256];
    HelpType		newhelp = NO_HELP;
    struct help_texts *t;

    snprintf(name, sizeof(name), "%.*s", MIN(url_len,sizeof(name)), url);

    for(t = h_texts; t->help_text != NO_HELP; t++)
      if(!strucmp(t->tag, name)){
	  newhelp = t->help_text;
	  break;
      }

    return(newhelp);
}
