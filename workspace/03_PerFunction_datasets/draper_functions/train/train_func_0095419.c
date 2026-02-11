location_is_none_20 (ats_ptr_type arg0) {

ATSlocal (ats_bool_type, tmp61) ;
ATSlocal (ats_lint_type, tmp62) ;

__ats_lab_location_is_none_20:
tmp62 = ats_selbox_mac(ats_castptr_mac(anairiats_rec_2, arg0), atslab_begpos_toff) ;
tmp61 = atspre_lt_lint_lint (tmp62, 0L) ;
return (tmp61) ;
}
