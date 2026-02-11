reader0_initialize_string_6 (ats_ref_type arg0, ats_ptr_type arg1, ats_ptr_type arg2) {


ATSlocal (ats_ptr_type, tmp16) ;
ATSlocal (ats_ptr_type, tmp18) ;

__ats_lab_reader0_initialize_string_6:
#line 126 "libatsdoc_reader.dats"
tmp16 = __ats_fun_7_closure_make (arg1, arg2) ;
#line 142 "libatsdoc_reader.dats"
tmp18 = __ats_fun_8_closure_make (arg2) ;
#line 147 "libatsdoc_reader.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_reader_struct, arg0), getchar) = tmp16 ;
#line 148 "libatsdoc_reader.dats"
ats_select_mac(ats_ptrget_mac(libatsdoc_reader_struct, arg0), freeres) = tmp18 ;
return  ;
}
