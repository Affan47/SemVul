__ats_fun_102 (anairiats_rec_1 arg0) {

ATSlocal (ats_bool_type, tmp440) ;
ATSlocal (ats_char_type, tmp441) ;

__ats_lab___ats_fun_102:
tmp441 = ats_select_mac(arg0, atslab_0) ;
tmp440 = atspre_string_contains (ATSstrcst("!%&$#+-./:<=>?@\\~`|*"), tmp441) ;
return (tmp440) ;
}
