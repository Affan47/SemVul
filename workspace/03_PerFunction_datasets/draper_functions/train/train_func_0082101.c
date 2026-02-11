__ats_fun_67 (ats_clo_ref_type env0, ats_clo_ref_type env1, ats_ptr_type env2, ats_ref_type arg0, ats_ref_type arg1, ats_ref_type arg2) {

ATSlocal (ats_ptr_type, tmp250) ;
ATSlocal (ats_ptr_type, tmp251) ;
ATSlocal (anairiats_rec_1, tmp252) ;
ATSlocal (ats_ptr_type, tmp253) ;
ATSlocal (ats_ptr_type, tmp254) ;
ATSlocal (ats_char_type, tmp255) ;

__ats_lab___ats_fun_67:
tmp251 = ((ats_ptr_type(*)(ats_clo_ptr_type, ats_ref_type, ats_ref_type, ats_ref_type))(ats_closure_fun(env0))) (env0, arg0, arg1, arg2) ;
do {

__ats_lab_57_0:
if (tmp251 == (ats_sum_ptr_type)0) { goto __ats_lab_60_0 ; }
__ats_lab_57_1:
tmp252 = ats_caselptrlab_mac(anairiats_sum_7, tmp251, atslab_0) ;
ATS_FREE(tmp251) ;
tmp253 = ((ats_ptr_type(*)(ats_clo_ptr_type, ats_ref_type, ats_ref_type, ats_ref_type))(ats_closure_fun(env1))) (env1, arg0, arg1, arg2) ;
do {

__ats_lab_58_0:
if (tmp253 == (ats_sum_ptr_type)0) { goto __ats_lab_59_0 ; }
__ats_lab_58_1:
tmp254 = ats_caselptrlab_mac(anairiats_sum_8, tmp253, atslab_0) ;
ATS_FREE(tmp253) ;
tmp255 = ((ats_char_type(*)(anairiats_rec_1, ats_ptr_type))env2) (tmp252, tmp254) ;
tmp250 = ATS_MALLOC(sizeof(anairiats_sum_10)) ;
ats_selptrset_mac(anairiats_sum_10, tmp250, atslab_0, tmp255) ;
break ;


__ats_lab_59_0:

__ats_lab_59_1:
tmp250 = tmp253 ;
break ;
} while (0) ;
break ;


__ats_lab_60_0:

__ats_lab_60_1:
tmp250 = tmp251 ;
break ;
} while (0) ;
return (tmp250) ;
}
