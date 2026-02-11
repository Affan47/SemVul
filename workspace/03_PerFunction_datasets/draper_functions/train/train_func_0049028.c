ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__position_incby_char (ats_ref_type arg0, ats_int_type arg1) {


ATSlocal (ats_bool_type, tmp17) ;
ATSlocal (ats_lint_type, tmp18) ;
ATSlocal (ats_lint_type, tmp19) ;
ATSlocal (ats_bool_type, tmp20) ;
ATSlocal (ats_int_type, tmp21) ;
ATSlocal (ats_int_type, tmp22) ;
ATSlocal (ats_int_type, tmp23) ;
ATSlocal (ats_int_type, tmp24) ;
ATSlocal (ats_int_type, tmp25) ;

__ats_lab_ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_location_2esats__position_incby_char:
#line 105 "libatsdoc_location.dats"
tmp17 = atspre_neq_int_int (arg1, EOF) ;
#line 105 "libatsdoc_location.dats"
if (tmp17) {
#line 110 "libatsdoc_location.dats"
tmp19 = ats_select_mac(ats_ptrget_mac(libatsdoc_position_struct, arg0), ntot) ;
#line 110 "libatsdoc_location.dats"
tmp18 = atspre_add_lint_lint (tmp19, 1L) ;
#line 110 "libatsdoc_location.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_position_struct, arg0), ntot) = tmp18 ;
#line 112 "libatsdoc_location.dats"
tmp21 = atspre_int_of_char ('\n') ;
#line 112 "libatsdoc_location.dats"
tmp20 = atspre_eq_int_int (arg1, tmp21) ;
#line 112 "libatsdoc_location.dats"
if (tmp20) {
#line 113 "libatsdoc_location.dats"
tmp23 = ats_select_mac(ats_ptrget_mac(libatsdoc_position_struct, arg0), nrow) ;
#line 113 "libatsdoc_location.dats"
tmp22 = atspre_add_int_int (tmp23, 1) ;
#line 113 "libatsdoc_location.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_position_struct, arg0), nrow) = tmp22 ;
#line 114 "libatsdoc_location.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_position_struct, arg0), ncol) = 0 ;
} else {
#line 118 "libatsdoc_location.dats"
tmp25 = ats_select_mac(ats_ptrget_mac(libatsdoc_position_struct, arg0), ncol) ;
#line 118 "libatsdoc_location.dats"
tmp24 = atspre_add_int_int (tmp25, 1) ;
#line 118 "libatsdoc_location.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_position_struct, arg0), ncol) = tmp24 ;
}
} else {

}
return  ;
}
