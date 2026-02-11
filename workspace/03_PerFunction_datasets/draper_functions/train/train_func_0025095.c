__ats_fun_15 (ats_ref_type arg0, ats_ref_type arg1, ats_ref_type arg2) {

ATSlocal (ats_ptr_type, tmp52) ;
ATSlocal (ats_ptr_type, tmp53) ;
ATSlocal (anairiats_rec_1, tmp54) ;
ATSlocal (ats_int_type, tmp55) ;
ATSlocal (ats_bool_type, tmp57) ;
ATSlocal (ats_ptr_type, tmp58) ;
ATSlocal (ats_ptr_type, tmp59) ;

__ats_lab___ats_fun_15:
tmp53 = stream_get_item_01890_anairiats_rec_1 (arg0) ;
do {

__ats_lab_11_0:
if (tmp53 == (ats_sum_ptr_type)0) { goto __ats_lab_12_0 ; }
__ats_lab_11_1:
tmp54 = ats_caselptrlab_mac(anairiats_sum_7, tmp53, atslab_0) ;
ATS_FREE(tmp53) ;
tmp55 = atspre_add_int_int (ats_ptrget_mac(ats_int_type, arg1), 1) ;
ats_ptrget_mac(ats_int_type, arg1) = tmp55 ;
tmp57 = atspre_gt_int_int (ats_ptrget_mac(ats_int_type, arg1), ats_ptrget_mac(ats_int_type, arg2)) ;
if (tmp57) {
ats_ptrget_mac(ats_int_type, arg2) = ats_ptrget_mac(ats_int_type, arg1) ;
} else {

}
tmp58 = ATS_MALLOC(sizeof(anairiats_sum_7)) ;
ats_selptrset_mac(anairiats_sum_7, tmp58, atslab_0, tmp54) ;
tmp52 = ATS_MALLOC(sizeof(anairiats_sum_8)) ;
ats_selptrset_mac(anairiats_sum_8, tmp52, atslab_0, tmp58) ;
break ;


__ats_lab_12_0:

__ats_lab_12_1:
tmp59 = (ats_sum_ptr_type)0 ;
tmp52 = ATS_MALLOC(sizeof(anairiats_sum_8)) ;
ats_selptrset_mac(anairiats_sum_8, tmp52, atslab_0, tmp59) ;
break ;
} while (0) ;
return (tmp52) ;
}
