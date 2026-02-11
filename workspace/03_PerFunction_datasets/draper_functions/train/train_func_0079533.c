aux_try_prepathlst_43 (ats_ptr_type arg0) {

ATSlocal (ats_ptr_type, tmp157) ;
ATSlocal (ats_ptr_type, tmp158) ;
ATSlocal (ats_ptr_type, tmp159) ;


__ats_lab_aux_try_prepathlst_43:
#line 478 "libatsdoc_filename.dats"
tmp158 = the_prepathlst_get_36 () ;
#line 479 "libatsdoc_filename.dats"
tmp159 = aux_try_41 (ats_castfn_mac(ats_ptr_type, tmp158), arg0) ;
#line 480 "libatsdoc_filename.dats"
 the_prepathlst_set_37 (tmp158) ;
#line 477 "libatsdoc_filename.dats"
tmp157 = tmp159 ;
return (tmp157) ;
}
