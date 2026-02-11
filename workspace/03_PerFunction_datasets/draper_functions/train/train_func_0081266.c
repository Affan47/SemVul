ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_filename_2esats__the_filenamelst_pop () {


ATSlocal (ats_ptr_type, tmp93) ;
ATSlocal (ats_ptr_type, tmp94) ;
ATSlocal (ats_ptr_type, tmp95) ;
ATSlocal (ats_ptr_type, tmp96) ;

__ats_lab_ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_filename_2esats__the_filenamelst_pop:
#line 295 "libatsdoc_filename.dats"
tmp93 = ats_selsin_mac(ats_castfn_mac(ats_ptr_type, statmp81), atslab_1) ;
#line 296 "libatsdoc_filename.dats"
tmp94 = ats_ptrget_mac(ats_ptr_type, tmp93) ;
#line 296 "libatsdoc_filename.dats"
if (tmp94 == (ats_sum_ptr_type)0) { ats_caseof_failure_handle ("/tmp/buildd/ats-lang-anairiats-0.2.11/libatsdoc/DATS/libatsdoc_filename.dats: 8376(line=296, offs=10) -- 8402(line=296, offs=36)") ; }
#line 296 "libatsdoc_filename.dats"
tmp95 = ats_caselptrlab_mac(anairiats_sum_1, tmp94, atslab_0) ;
#line 296 "libatsdoc_filename.dats"
tmp96 = ats_caselptrlab_mac(anairiats_sum_1, tmp94, atslab_1) ;
#line 296 "libatsdoc_filename.dats"
ATS_FREE(tmp94) ;
#line 297 "libatsdoc_filename.dats"
ats_ptrget_mac(ats_ptr_type, tmp93) = tmp96 ;
#line 299 "libatsdoc_filename.dats"
ats_ptrget_mac(ats_ptr_type, statmp77) = tmp95 ;
return  ;
}
