detect_filetype (char *fname, gretlopt opt)
{
    int i, c, ftype = GRETL_NATIVE_DATA;
    FILE *fp;


    if (has_suffix(fname, ".inp")) {
	return GRETL_SCRIPT;
    }

    if (has_suffix(fname, ".gretl")) {
	if (gretl_is_pkzip_file(fname)) {
	    return GRETL_SESSION;
	} else {
	    return GRETL_SCRIPT;
	}
    }

    if (has_suffix(fname, ".gnumeric"))
	return GRETL_GNUMERIC;
    if (has_suffix(fname, ".xlsx"))
	return GRETL_XLSX;
    if (has_suffix(fname, ".xls"))
	return GRETL_XLS;
    if (has_suffix(fname, ".ods"))
	return GRETL_ODS;
    if (has_suffix(fname, ".wf1"))
	return GRETL_WF1;
    if (has_suffix(fname, ".dta"))
	return GRETL_DTA;
    if (has_suffix(fname, ".sav"))
	return GRETL_SAV;
    if (has_suffix(fname, ".xpt"))
	return GRETL_SAS;
    if (has_suffix(fname, ".bin"))
	return GRETL_NATIVE_DB;
    if (has_suffix(fname, ".rat"))
	return GRETL_RATS_DB;
    if (has_suffix(fname, ".csv"))
	return GRETL_CSV;
    if (has_suffix(fname, ".txt"))
	return GRETL_CSV;
    if (has_suffix(fname, ".asc"))
	return GRETL_CSV;
    if (has_suffix(fname, ".m"))
	return GRETL_OCTAVE;
    if (has_suffix(fname, ".bn7"))
	return GRETL_PCGIVE_DB;

    if (opt & OPT_P) {
	gretl_addpath(fname, 0);
    }

    if (gretl_is_xml_file(fname)) {
	return GRETL_XML_DATA;
    }

    if (has_suffix(fname, ".dat") && is_jmulti_datafile(fname)) {
	return GRETL_JMULTI;
    }

    fp = gretl_fopen(fname, "r");
    if (fp == NULL) {

	return GRETL_NATIVE_DATA;
    }


    for (i=0; i<80; i++) {
	c = getc(fp);
	if (c == EOF || c == '\n') {
	    break;
	}
	if (!isprint(c) && c != '\r' && c != '\t') {
	    ftype = GRETL_NATIVE_DATA;
	    break;
	}
    }

    fclose(fp);

    return ftype;
}
