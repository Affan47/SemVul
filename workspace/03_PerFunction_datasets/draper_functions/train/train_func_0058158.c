wvsp_one(fp, idx, s, sc)
    FILE	*fp;
    int		idx;
    char	*s;
    int		sc;
{
    if (spats[idx].pat != NULL)
    {
	fprintf(fp, _("\n# Last %sSearch Pattern:\n~"), s);

	fprintf(fp, "%c%c%c%c%ld%s%c",
		spats[idx].magic    ? 'M' : 'm',
		spats[idx].no_scs   ? 's' : 'S',
		spats[idx].off.line ? 'L' : 'l',
		spats[idx].off.end  ? 'E' : 'e',
		spats[idx].off.off,
		last_idx == idx	    ? "~" : "",
		sc);
	viminfo_writestring(fp, spats[idx].pat);
    }
}
