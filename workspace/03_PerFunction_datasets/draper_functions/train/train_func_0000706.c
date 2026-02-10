f_93 (anairiats_rec_12 arg0) {

ATSlocal (ats_ptr_type, tmp399) ;
ATSlocal (anairiats_rec_1, tmp400) ;
ATSlocal (ats_ptr_type, tmp401) ;
ATSlocal (ats_ptr_type, tmp402) ;
ATSlocal (anairiats_rec_11, tmp403) ;
ATSlocal (ats_ptr_type, tmp404) ;
ATSlocal (ats_ptr_type, tmp405) ;
ATSlocal (ats_int_type, tmp406) ;
ATSlocal (ats_int_type, tmp407) ;

__ats_lab_f_93:
tmp400 = ats_select_mac(arg0, atslab_0) ;
tmp401 = ats_select_mac(arg0, atslab_1) ;
tmp402 = ats_select_mac(tmp400, atslab_1) ;
tmp403 = loop_89 (tmp401, 0, tmp402) ;
tmp405 = ats_select_mac(tmp403, atslab_1) ;
tmp404 = ATS_2d0_2e2_2e11_2contrib_2parcomb_2SATS_2posloc_2esats__location_make (tmp402, tmp405) ;
tmp407 = ats_select_mac(tmp403, atslab_0) ;
tmp406 = atspre_neg_int (tmp407) ;
tmp399 = token_int_make_5 (tmp404, tmp406) ;
return (tmp399) ;
}
