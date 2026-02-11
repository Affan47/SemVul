Has_ACPI(char *c)
{
    ifstream file_in, file2_in;
    char *filename, *filename2, str[50];

    filename = "/proc/acpi/info";
    filename2 = "/sys/module/acpi/parameters/acpica_version";

    file_in.open(filename);
    file2_in.open(filename2);

    if (!file_in && !file2_in)
    {
    	cout<<"  Could not open any of these files : "<<filename<<", "<<filename2<<endl;
	cout<<"  Make sure your kernel has ACPI support enabled."<<endl;
	strcpy(c, "n.a");
	return 0;
    }
    else
    {
	if(file_in)
	{
	    file_in.getline(str, 50);
	    file_in.close();
	    strncpy(c, str+25,8);
	    Use_Proc = 1;


	    return 1;
	}
	if(file2_in)
	{
	    file2_in.getline(str, 50);
	    file2_in.close();
	    strncpy(c, str,8);
	    Use_Sys = 1;


	    return 1;
	}
    }
}
