loop_32 (ats_ptr_type arg0, ats_ptr_type arg1, ats_ptr_type arg2) {


ATSlocal (ats_ptr_type, tmp91) ;
ATSlocal (ats_ptr_type, tmp92) ;


__ats_lab_loop_32:
#line 92 "list.dats"
do {

#line 93 "list.dats"
__ats_lab_13_0:
#line 93 "list.dats"
if (arg0 == (ats_sum_ptr_type)0) { goto __ats_lab_14_0 ; }
#line 93 "list.dats"
__ats_lab_13_1:
#line 93 "list.dats"
tmp91 = ats_caselptrlab_mac(anairiats_sum_4, arg0, atslab_0) ;
#line 93 "list.dats"
tmp92 = ats_caselptrlab_mac(anairiats_sum_4, arg0, atslab_1) ;
#line 94 "list.dats"
 ((ats_void_type(*)(ats_ptr_type, ats_ptr_type))arg1) (tmp91, arg2) ;
#line 94 "list.dats"
arg0 = tmp92 ;
#line 94 "list.dats"
arg1 = arg1 ;
#line 94 "list.dats"
arg2 = arg2 ;
#line 94 "list.dats"
goto __ats_lab_loop_32 ;
break ;


#line 96 "list.dats"
__ats_lab_14_0:
#line 96 "list.dats"

#line 96 "list.dats"
__ats_lab_14_1:
break ;
} while (0) ;
return  ;
}
