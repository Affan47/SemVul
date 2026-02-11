stripspaces(char *name)
{
	char *p,*non_space;

	non_space = name;
	for(p=name; *p; p++)
		if (*p != ' ')
			non_space = p;
	if(name[0])
		non_space[1] = '\0';
}
