cgcef_delscn(CGCEf *cgcef, CGCEf_Scn *scn) {
    CGCEf_Scn *pscn;
    Scn_Data *sd;
    Scn_Data *tmp;
    size_t index;

    if (!cgcef || !scn) {
	return SHN_UNDEF;
    }
    cgcef_assert(cgcef->e_magic == CGCEF_MAGIC);
    cgcef_assert(scn->s_magic == SCN_MAGIC);
    cgcef_assert(cgcef->e_ehdr);
    if (scn->s_cgcef != cgcef) {
	seterr(ERROR_CGCEFSCNMISMATCH);
	return SHN_UNDEF;
    }
    cgcef_assert(cgcef->e_scn_1);
    if (scn == cgcef->e_scn_1) {
	seterr(ERROR_NULLSCN);
	return SHN_UNDEF;
    }


    for (pscn = cgcef->e_scn_1; pscn->s_link; pscn = pscn->s_link) {
	if (pscn->s_link == scn) {
	    break;
	}
    }
    if (pscn->s_link != scn) {
	seterr(ERROR_CGCEFSCNMISMATCH);
	return SHN_UNDEF;
    }


    if (cgcef->e_scn_n == scn) {
	cgcef->e_scn_n = pscn;
    }
    pscn->s_link = scn->s_link;
    index = scn->s_index;


    for (sd = scn->s_data_1; sd; sd = tmp) {
	cgcef_assert(sd->sd_magic == DATA_MAGIC);
	cgcef_assert(sd->sd_scn == scn);
	tmp = sd->sd_link;
	if (sd->sd_free_data && sd->sd_memdata) {
	    free(sd->sd_memdata);
	}
	if (sd->sd_freeme) {
	    free(sd);
	}
    }
    if ((sd = scn->s_rawdata)) {
	cgcef_assert(sd->sd_magic == DATA_MAGIC);
	cgcef_assert(sd->sd_scn == scn);
	if (sd->sd_free_data && sd->sd_memdata) {
	    free(sd->sd_memdata);
	}
	if (sd->sd_freeme) {
	    free(sd);
	}
    }
    if (scn->s_freeme) {
	cgcef_assert(scn->s_index > 0);
	free(scn);
    }


    for (scn = pscn->s_link; scn; scn = scn->s_link) {
	cgcef_assert(scn->s_index > index);
	scn->s_index--;
    }


    if (cgcef->e_class == CGCEFCLASS32) {
	_cgcef32_update_shdr(cgcef, index);
	return index;
    }
#if __LIBCGCEF64
    else if (cgcef->e_class == CGCEFCLASS64) {
	_cgcef64_update_shdr(cgcef, index);
	return index;
    }
#endif
    else if (valid_class(cgcef->e_class)) {
	seterr(ERROR_UNIMPLEMENTED);
    }
    else {
	seterr(ERROR_UNKNOWN_CLASS);
    }
    return SHN_UNDEF;
}
