cgcef64_getshdr(CGCEf_Scn *scn) {
    if (!scn) {
	return NULL;
    }
    cgcef_assert(scn->s_magic == SCN_MAGIC);
    cgcef_assert(scn->s_cgcef);
    cgcef_assert(scn->s_cgcef->e_magic == CGCEF_MAGIC);
    if (scn->s_cgcef->e_class == CGCEFCLASS64) {
	return &scn->s_shdr64;
    }
    seterr(ERROR_CLASSMISMATCH);
    return NULL;
}
