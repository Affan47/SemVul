printremotemta(const char *p, const char type, void *q)
{
struct dsndiagnosticinfo *i=(struct dsndiagnosticinfo *)q;

	if (type == COMCTLFILE_DELINFO_PEER && i->flag == 0)
	{
		fprintf(i->fp, "Remote-MTA: dns; %s\n", p);
		i->flag=1;
	}
}
