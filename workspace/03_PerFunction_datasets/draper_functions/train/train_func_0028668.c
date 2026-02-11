f_29 (anairiats_rec_1 arg0) {

ATSlocal (ats_ptr_type, tmp94) ;
ATSlocal (ats_ptr_type, tmp95) ;
ATSlocal (ats_ptr_type, tmp96) ;
ATSlocal (ats_char_type, tmp97) ;

__ats_lab_f_29:
tmp95 = ats_select_mac(arg0, atslab_1) ;
tmp96 = ATS_2d0_2e2_2e11_2contrib_2parcomb_2SATS_2posloc_2esats__location_make (tmp95, tmp95) ;
tmp97 = ats_select_mac(arg0, atslab_0) ;
tmp94 = ATS_2d0_2e2_2e11_2contrib_2parcomb_2DATS_2tokenize_2edats__token_singleton_make (tmp96, tmp97) ;
return (tmp94) ;
}
