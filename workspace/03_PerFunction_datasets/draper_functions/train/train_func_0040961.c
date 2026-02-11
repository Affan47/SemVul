is_vms_name(char *name)
{
    if ( (strchr(name, '[') && strchr(name, ']')) ||
	  strchr(name, ';') || strchr(name, ':') )
	return vms_format=true;


    unsigned int i;
    bool allupper = true;
    for (i=0; i<strlen(name); i++)
	    if (!isupper(name[i]))
		    allupper = false;

    if (allupper && strlen(name))
	    return vms_format=true;
    else
	    return vms_format=false;
}
