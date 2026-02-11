restore()
{
	register int	i;
	char	tofile[FILESIZE],
		answer[SMALLSTRSIZE];
	int	nrecovered = 0;

	for (i = 1; i <= Header.Nbuffers; i++) {
		(void) sprintf(tofile, "#%s", buflist[i]->r_bname);
tryagain:
		printf("Restoring %s to %s, okay?", buflist[i]->r_bname,
						     tofile);
		tellme(" ", answer, sizeof(answer));
		switch (answer[0]) {
		case 'y':
			break;

		case 'n':
			continue;

		default:
			tellme("What file should I use instead? ", tofile,
			       sizeof(tofile));
			goto tryagain;
		}
		get(&buflist[i], tofile);
		nrecovered += 1;
	}
	printf("Recovered %d buffers.\n", nrecovered);
}
