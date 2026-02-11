cleanup_i(IN_PAR * pi)
{
	if (pi != NULL && pi->hd != NULL) {
		if (pi->hd != stdin)
			fclose(pi->hd);
		pi->hd = NULL;
	}
}
