pr(ip, file, base)
	register struct inclist  *ip;
	char	*file, *base;
{
	static char	*lastfile;
	static int	current_len;
	register int	len, i;
	char	buf[ BUFSIZ ];

	printed = TRUE;
	len = strlen(ip->i_file)+1;
	if (current_len + len > width || file != lastfile) {
		lastfile = file;
		sprintf(buf, "\n%s%s%s: %s", objprefix, base, objsuffix,
			ip->i_file);
		len = current_len = strlen(buf);
	}
	else {
		buf[0] = ' ';
		strcpy(buf+1, ip->i_file);
		current_len += len;
	}
	fwrite(buf, len, 1, stdout);


	if (! verbose || ip->i_list == NULL || ip->i_flags & NOTIFIED)
		return;
	ip->i_flags |= NOTIFIED;
	lastfile = NULL;
	printf("\n# %s includes:", ip->i_file);
	for (i=0; i<ip->i_listlen; i++)
		printf("\n#\t%s", ip->i_list[ i ]->i_incstring);
}
