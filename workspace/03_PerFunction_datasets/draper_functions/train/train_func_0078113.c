read_in7_series_info (FILE *fp, dbwrapper *dw)
{
    char line[1024];
    char sname[VNAMELEN];
    char desc[MAXLABEL];
    char fmt[24];
    int y0, p0, y1, p1;
    int pd, offset, pos;
    int i, nf;
    int err = 0;

    sprintf(fmt, "%%%ds %%d %%d %%d %%d %%d %%d", VNAMELEN - 1);

    i = 0;
    while (fgets(line, sizeof line, fp) && !err) {
	if (*line == '>') {
	    nf = sscanf(line + 1, fmt, sname, &y0, &p0, &y1,
			&p1, &pd, &offset);
	    if (nf == 7 && y0 > 0 && p0 > 0 && y1 > 0 && p1 > 0 &&
		pd >= 1 && offset > 0) {
		*desc = 0;
		pos = ftell(fp);
		while (fgets(line, sizeof line, fp)) {
		    if (*line == ';') {

			int rem = MAXLABEL - strlen(desc) - 1;

			if (rem > 0) {
			    gretl_strstrip(line);
			    strncat(desc, line + 1, rem);
			}
			pos = ftell(fp);
		    } else {

			fseek(fp, pos, SEEK_SET);
			break;
		    }
		}

		err = in7_to_sinfo(sname, desc, y0, p0, y1, p1,
				   pd, offset, &dw->sinfo[i++]);
		if (!err) {
		    dw->nv += 1;
		}
	    }
	}
    }

    return err;
}
