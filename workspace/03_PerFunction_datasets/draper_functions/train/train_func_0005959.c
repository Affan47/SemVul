append_mtab(FILE *fp, FILE *ofp, struct mntent *ent)
{
	int err;
	struct mntent *p;

	while ((p = getmntent(ofp))) {
		err = addmntent(fp, p);
		if (err)
			AuFin("addmntent");
	}

	err = addmntent(fp, ent);
	if (err)
		AuFin("addmntent");
}
