ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_lexbuf_2esats__lexbufpos_get_char (ats_ref_type arg0, ats_ref_type arg1) {

ATSlocal (ats_int_type, tmp65) ;
ATSlocal (ats_lint_type, tmp66) ;
ATSlocal (ats_lint_type, tmp67) ;
ATSlocal (ats_lint_type, tmp68) ;
ATSlocal (ats_uint_type, tmp69) ;

__ats_lab_ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_lexbuf_2esats__lexbufpos_get_char:
#line 258 "libatsdoc_lexbuf.dats"
tmp67 = ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__position_get_ntot (arg1) ;
#line 258 "libatsdoc_lexbuf.dats"
tmp68 = ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), base) ;
#line 258 "libatsdoc_lexbuf.dats"
tmp66 = atspre_sub_lint_lint (tmp67, tmp68) ;
#line 259 "libatsdoc_lexbuf.dats"
tmp69 = atspre_uint_of_lint (tmp66) ;
#line 261 "libatsdoc_lexbuf.dats"
tmp65 = ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_lexbuf_2esats__lexbuf_get_char (arg0, tmp69) ;
return (tmp65) ;
}
