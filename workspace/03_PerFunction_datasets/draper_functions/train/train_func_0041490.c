tty_is_locked(char *tty)
{
	char buffer[50], *s;
	FILE *fp;
	int pid = 0;

	if ((s = strrchr(tty, '/')) != NULL)
		s++;
	else
		s = tty;

	sprintf(buffer, "%s/LCK..%s", LOCK_SERIAL_DIR, s);

	if ((fp = fopen(buffer, "r")) == NULL)
		return FALSE;

	if (fscanf(fp, "%d", &pid) != 1) {
		fclose(fp);
		return FALSE;
	}

	fclose(fp);

	if (kill(pid, 0) == 0)
		return TRUE;

	return FALSE;
}
