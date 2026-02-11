ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_lexbuf_2esats__lexbuf_reset_position (ats_ref_type arg0, ats_ref_type arg1) {


ATSlocal (ats_lint_type, tmp99) ;
ATSlocal (ats_lint_type, tmp100) ;
ATSlocal (ats_lint_type, tmp101) ;
ATSlocal (ats_int_type, tmp102) ;
ATSlocal (ats_int_type, tmp103) ;
ATSlocal (ats_size_type, tmp104) ;
ATSlocal (ats_bool_type, tmp105) ;

__ats_lab_ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_lexbuf_2esats__lexbuf_reset_position:
#line 299 "libatsdoc_lexbuf.dats"
tmp99 = ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__position_get_ntot (arg1) ;
#line 300 "libatsdoc_lexbuf.dats"
tmp101 = ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), base) ;
#line 300 "libatsdoc_lexbuf.dats"
tmp100 = atspre_sub_lint_lint (tmp99, tmp101) ;
#line 301 "libatsdoc_lexbuf.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), base) = tmp99 ;
#line 302 "libatsdoc_lexbuf.dats"
tmp102 = ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__position_get_nrow (arg1) ;
#line 302 "libatsdoc_lexbuf.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), base_nrow) = tmp102 ;
#line 303 "libatsdoc_lexbuf.dats"
tmp103 = ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__position_get_ncol (arg1) ;
#line 303 "libatsdoc_lexbuf.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), base_ncol) = tmp103 ;
#line 306 "libatsdoc_lexbuf.dats"
tmp104 = ATS_2d0_2e2_2e11_2libats_2SATS_2linqueue_arr_2esats__queue_size (&ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), cbuf)) ;
#line 308 "libatsdoc_lexbuf.dats"
tmp105 = atspre_lt_size1_size1 (ats_castfn_mac(ats_size_type, ats_castfn_mac(ats_size_type, tmp100)), tmp104) ;
#line 308 "libatsdoc_lexbuf.dats"
if (tmp105) {
#line 309 "libatsdoc_lexbuf.dats"
 queue_clear_01755_ats_uchar_type (&ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), cbuf), ats_castfn_mac(ats_size_type, ats_castfn_mac(ats_size_type, tmp100))) ;
} else {
#line 313 "libatsdoc_lexbuf.dats"
 ATS_2d0_2e2_2e11_2libats_2SATS_2linqueue_arr_2esats__queue_clear_all (&ats_select_mac(ats_ptrget_mac(libatsdoc_lexbuf_struct, arg0), cbuf)) ;
}
return  ;
}
