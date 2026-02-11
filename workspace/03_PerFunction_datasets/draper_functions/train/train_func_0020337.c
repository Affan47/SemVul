check_norc(int argc, char * argv[])
{
    int i = 1;
    while (i < argc)
    {
	if (strcmp(argv[i], "--norc") == 0)
	{
	    norc = "-f";
	    break;
	}
	i++;
    }
}
