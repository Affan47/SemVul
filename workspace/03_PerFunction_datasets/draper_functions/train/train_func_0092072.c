Do_AC_Info(int verbose)
{
    ifstream file_in;
    char *dirname, filename[4][50], str[40];
    int ac_count = 0;
    DIR *ac_dir;
    struct dirent *ac_dirent;
    char *name;
    char AC_Status[9];

    memset(AC_Status, '\0', 9);

    dirname = "/proc/acpi/ac_adapter/";
    ac_dir = opendir(dirname);
    if(ac_dir)
    {
    	while((ac_dirent = readdir(ac_dir)))
  	{
	    name = ac_dirent->d_name;

    	    if (!strcmp (".", name) || !strcmp ("..", name)) continue;
       	    sprintf(filename[ac_count], "/proc/acpi/ac_adapter/%s/state", name);
       	    ac_count++;
       	}
    }
    closedir(ac_dir);

    if(ac_count>0)
    	Do_AC_Info_Proc(verbose);
    else
	Do_AC_Info_Sys();

    return 0;
}
