c_missing_noreturn_ok_p (decl)
     tree decl;
{


  return flag_hosted && MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl));
}
