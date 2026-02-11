freecomm(comm, nown)
command_t *comm;
int nown;
{
	int i;

	if (!comm) return;
	if (comm -> argv) {
		if (isstatement(comm))
			freestree((syntaxtree *)(comm -> argv));
		else for (i = 0; i <= comm -> argc; i++)
			Xfree(comm -> argv[i]);
		Xfree(comm -> argv);
	}
	if (comm -> redp) {
		closeredirect(comm -> redp);
		freerlist(comm -> redp, nown);
	}
	Xfree(comm);
}
