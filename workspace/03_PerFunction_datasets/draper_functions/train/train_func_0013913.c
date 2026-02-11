do_ctlr(void)
{
	if (*standard_font) {
		status_add(LBOX, '4', KT_STD);
		if (oia_undera)
			status_add(CNCT, (IN_E ? 'B' : 'A'), KT_STD);
		else
			status_add(CNCT, ' ', KT_STD);
		if (IN_ANSI)
			status_add(RBOX, 'N', KT_STD);
		else if (oia_boxsolid)
			status_add(RBOX, ' ', KT_STD);
		else if (IN_SSCP)
			status_add(RBOX, 'S', KT_STD);
		else
			status_add(RBOX, '?', KT_STD);
	} else {
		status_add(LBOX, CG_box4, KT_STD);
		if (oia_undera)
			status_add(CNCT, (IN_E ? CG_underB : CG_underA),
				KT_STD);
		else
			status_add(CNCT, CG_null, KT_STD);
		if (IN_ANSI)
			status_add(RBOX, CG_N, KT_STD);
		else if (oia_boxsolid)
			status_add(RBOX, CG_boxsolid, KT_STD);
		else if (IN_SSCP)
			status_add(RBOX, CG_boxhuman, KT_STD);
		else
			status_add(RBOX, CG_boxquestion, KT_STD);
	}
}
