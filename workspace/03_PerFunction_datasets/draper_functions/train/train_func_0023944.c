unsetcmd(int argc, char **argv)
{
	char **ap;
	int i;
	int flag = 0;

	while ((i = nextopt("vf")) != '\0') {
		flag = i;
	}

	for (ap = argptr; *ap ; ap++) {
		if (flag != 'f') {
			unsetvar(*ap);
			continue;
		}
		if (flag != 'v')
			unsetfunc(*ap);
	}
	return 0;
}
