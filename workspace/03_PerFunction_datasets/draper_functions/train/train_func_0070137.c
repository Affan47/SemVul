format_cid(cid, str)

int			cid;
char			*str;

{
	int 		collective;

	collective = (cid < 0);

	cid = lam_coll2pt(cid);

	if (cid == 0) {
		strcpy(str, "WORLD");
	}
	else if (cid == 1) {
		strcpy(str, "SELF");
	}
	else {
		sprintf(str, "<%d>", cid);
	}

	if (collective) strcat(str, "*");
}
