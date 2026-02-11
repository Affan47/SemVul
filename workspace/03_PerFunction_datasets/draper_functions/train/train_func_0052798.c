eqn_restriction_set_start (const char *line, MODEL *pmod,
			   const DATASET *dset,
			   gretlopt opt)
{
    gretl_restriction *rset;

    rset = restriction_set_new(pmod, GRETL_OBJ_EQN, opt);
    if (rset == NULL) {
	gretl_errmsg_set(_("Out of memory!"));
	return NULL;
    }

    if (real_restriction_set_parse_line(rset, line, dset, 1)) {
	gretl_errmsg_sprintf(_("parse error in '%s'\n"), line);
	return NULL;
    }

    return rset;
}
