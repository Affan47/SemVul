ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_symbol_2esats__neq_symbol_symbol (ats_ptr_type arg0, ats_ptr_type arg1) {

ATSlocal (ats_bool_type, tmp114) ;
ATSlocal (ats_uint_type, tmp115) ;
ATSlocal (ats_uint_type, tmp116) ;

__ats_lab_ATS_2d0_2e2_2e11_2libatsdoc_2SATS_2libatsdoc_symbol_2esats__neq_symbol_symbol:
#line 220 "libatsdoc_symbol.dats"
tmp115 = ats_selbox_mac(ats_castptr_mac(anairiats_rec_2, arg0), atslab_stamp) ;
#line 220 "libatsdoc_symbol.dats"
tmp116 = ats_selbox_mac(ats_castptr_mac(anairiats_rec_2, arg1), atslab_stamp) ;
#line 220 "libatsdoc_symbol.dats"
tmp114 = atspre_neq_uint_uint (tmp115, tmp116) ;
return (tmp114) ;
}
