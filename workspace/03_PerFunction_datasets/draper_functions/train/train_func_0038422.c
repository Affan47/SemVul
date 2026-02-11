hashtbl_ptr_split_044_string_2csymbol (ats_ptr_type arg0, ats_size_type arg1) {

ATSlocal (ats_ptr_type, tmp24) ;
ATSlocal (ats_size_type, tmp25) ;
ATSlocal (ats_size_type, tmp26) ;

__ats_lab_hashtbl_ptr_split_044_string_2csymbol:
#line 180 "hashtable_linprb.dats"
tmp25 = atspre_mul2_size1_size1 (arg1, sizeof(anairiats_rec_0)) ;
#line 180 "hashtable_linprb.dats"
tmp26 = ats_selsin_mac(tmp25, atslab_1) ;
#line 183 "hashtable_linprb.dats"
tmp24 = atspre_padd_size (arg0, tmp26) ;
return (tmp24) ;
}
