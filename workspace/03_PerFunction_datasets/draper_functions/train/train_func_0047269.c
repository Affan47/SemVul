ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__fprint_position (ats_ptr_type arg0, libatsdoc_position_struct arg1) {


ATSlocal (ats_lint_type, tmp1) ;
ATSlocal (ats_int_type, tmp2) ;
ATSlocal (ats_int_type, tmp3) ;
ATSlocal (ats_lint_type, tmp4) ;
ATSlocal (ats_int_type, tmp5) ;
ATSlocal (ats_int_type, tmp6) ;

__ats_lab_ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__fprint_position:
#line 63 "libatsdoc_location.dats"
tmp1 = ats_select_mac(arg1, ntot) ;
#line 64 "libatsdoc_location.dats"
tmp2 = ats_select_mac(arg1, nrow) ;
#line 65 "libatsdoc_location.dats"
tmp3 = ats_select_mac(arg1, ncol) ;
#line 67 "libatsdoc_location.dats"
tmp4 = atspre_add_lint_lint (tmp1, 1L) ;
#line 67 "libatsdoc_location.dats"
tmp5 = atspre_add_int_int (tmp2, 1) ;
#line 67 "libatsdoc_location.dats"
tmp6 = atspre_add_int_int (tmp3, 1) ;
#line 66 "libatsdoc_location.dats"
 atspre_fprintf_exn (arg0, ATSstrcst("%li(line=%i, offs=%i)"), tmp4, tmp5, tmp6) ;
return  ;
}
