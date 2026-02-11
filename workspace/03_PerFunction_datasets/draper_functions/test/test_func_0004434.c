VAR_info_header_block (int code, int v, int block,
				   const DATASET *dset,
				   PRN *prn)
{
    int tex = tex_format(prn);
    int rtf = rtf_format(prn);
    char vname[32];

    if (tex) {
	pputs(prn, "\\vspace{1em}\n\n");
	if (code == IRF) {
	    pprintf(prn, A_("Responses to a one-standard error shock in %s"),
		    tex_escape(vname, dset->varname[v]));
	} else {
	    pprintf(prn, A_("Decomposition of variance for %s"),
		    tex_escape(vname, dset->varname[v]));
	}
	if (block == 0) {
	    pputs(prn, "\n\n");
	} else {
	    pprintf(prn, " (%s)\n\n", A_("continued"));
	}
	pprintf(prn, "\\vspace{1em}\n\n\\begin{longtable}{%s}\n",
		(code == IRF)? "rrrrr" : "rrrrrr");
    } else if (rtf) {
	pputs(prn, "\\par\n\n");
	if (code == IRF) {
	    pprintf(prn, A_("Responses to a one-standard error shock in %s"),
		    dset->varname[v]);
	} else {
	    pprintf(prn, A_("Decomposition of variance for %s"),
		    dset->varname[v]);
	}
	if (block == 0) {
	    pputs(prn, "\\par\n\n");
	} else {
	    pprintf(prn, " (%s)\\par\n\n", A_("continued"));
	}

	VAR_RTF_row_spec((code == IRF)? IRF_ROW_MAX : VDC_ROW_MAX, prn);
    } else {
	if (code == IRF) {
	    pprintf(prn, _("Responses to a one-standard error shock in %s"),
		    dset->varname[v]);
	} else {
	    pprintf(prn, _("Decomposition of variance for %s"),
		    dset->varname[v]);
	}
	if (block == 0) {
	    pputs(prn, "\n\n");
	} else {
	    pprintf(prn, " (%s)\n\n", _("continued"));
	}
    }


    if (tex) {
	pprintf(prn, "%s & ", A_("period"));
    } else if (rtf) {
	pprintf(prn, "\\intbl \\qc %s\\cell ", A_("period"));
    } else {
	pputs(prn, _("period"));
    }
}
