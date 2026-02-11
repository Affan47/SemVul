loop_89 (ats_ptr_type arg0, ats_int_type arg1, ats_ptr_type arg2) {

ATSlocal (anairiats_rec_11, tmp374) ;
ATSlocal (anairiats_rec_1, tmp375) ;
ATSlocal (ats_ptr_type, tmp376) ;
ATSlocal (ats_int_type, tmp377) ;
ATSlocal (ats_int_type, tmp378) ;
ATSlocal (ats_char_type, tmp379) ;
ATSlocal (ats_int_type, tmp380) ;
ATSlocal (ats_ptr_type, tmp381) ;

__ats_lab_loop_89:
do {

__ats_lab_89_0:
if (arg0 == (ats_sum_ptr_type)0) { goto __ats_lab_90_0 ; }
__ats_lab_89_1:
tmp375 = ats_caselptrlab_mac(anairiats_sum_2, arg0, atslab_0) ;
tmp376 = ats_caselptrlab_mac(anairiats_sum_2, arg0, atslab_1) ;
tmp379 = ats_select_mac(tmp375, atslab_0) ;
tmp378 = atspre_sub_char_char (tmp379, '0') ;
tmp380 = atspre_mul_int_int (10, arg1) ;
tmp377 = atspre_add_int_int (tmp378, tmp380) ;
tmp381 = ats_select_mac(tmp375, atslab_1) ;
arg0 = tmp376 ;
arg1 = tmp377 ;
arg2 = tmp381 ;
goto __ats_lab_loop_89 ;
break ;


__ats_lab_90_0:

__ats_lab_90_1:
tmp374.atslab_0 = arg1 ;
tmp374.atslab_1 = arg2 ;

break ;
} while (0) ;
return (tmp374) ;
}
