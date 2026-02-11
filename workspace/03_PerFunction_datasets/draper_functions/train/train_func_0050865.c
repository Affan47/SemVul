is_vmlinux(const char *modname)
{
	const char *myname;

	myname = strrchr(modname, '/');
	if (myname)
		myname++;
	else
		myname = modname;

	return (strcmp(myname, "vmlinux") == 0) ||
	       (strcmp(myname, "vmlinux.o") == 0);
}
