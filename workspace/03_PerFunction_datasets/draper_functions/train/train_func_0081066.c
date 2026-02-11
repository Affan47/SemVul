HdlrFunc2 (
 Obj  self,
 Obj  a_list )
{
 Obj t_1 = 0;
 Obj t_2 = 0;
 Obj t_3 = 0;
 Obj t_4 = 0;
 Obj t_5 = 0;
 Obj t_6 = 0;
 Obj t_7 = 0;
 Obj t_8 = 0;
 Obj t_9 = 0;
 Obj t_10 = 0;
 Obj t_11 = 0;
 Bag oldFrame;
 OLD_BRK_CURR_STAT


 SWITCH_TO_NEW_FRAME(self,0,0,oldFrame);
 REM_BRK_CURR_STAT();
 SET_BRK_CURR_STAT(0);


 t_3 = GC_R__N;
 CHECK_BOUND( t_3, "R_N" )
 t_2 = MOD( t_3, INTOBJ_INT(55) );
 C_SUM_FIA( t_1, t_2, INTOBJ_INT(1) )
 AssGVar( G_R__N, t_1 );


 t_1 = GC_R__X;
 CHECK_BOUND( t_1, "R_X" )
 t_2 = GC_R__N;
 CHECK_BOUND( t_2, "R_N" )
 CHECK_INT_POS( t_2 )
 t_6 = GC_R__X;
 CHECK_BOUND( t_6, "R_X" )
 t_7 = GC_R__N;
 CHECK_BOUND( t_7, "R_N" )
 CHECK_INT_POS( t_7 )
 C_ELM_LIST_FPL( t_5, t_6, t_7 )
 t_7 = GC_R__X;
 CHECK_BOUND( t_7, "R_X" )
 t_11 = GC_R__N;
 CHECK_BOUND( t_11, "R_N" )
 C_SUM_FIA( t_10, t_11, INTOBJ_INT(30) )
 t_9 = MOD( t_10, INTOBJ_INT(55) );
 C_SUM_FIA( t_8, t_9, INTOBJ_INT(1) )
 CHECK_INT_POS( t_8 )
 C_ELM_LIST_FPL( t_6, t_7, t_8 )
 C_SUM_FIA( t_4, t_5, t_6 )
 t_5 = GC_R__228;
 CHECK_BOUND( t_5, "R_228" )
 t_3 = MOD( t_4, t_5 );
 C_ASS_LIST_FPL( t_1, t_2, t_3 )


 t_4 = GF_QUO__INT;
 t_7 = GC_R__X;
 CHECK_BOUND( t_7, "R_X" )
 t_8 = GC_R__N;
 CHECK_BOUND( t_8, "R_N" )
 CHECK_INT_POS( t_8 )
 C_ELM_LIST_FPL( t_6, t_7, t_8 )
 t_8 = GF_LEN__LIST;
 t_7 = CALL_1ARGS( t_8, a_list );
 CHECK_FUNC_RESULT( t_7 )
 C_PROD_FIA( t_5, t_6, t_7 )
 t_6 = GC_R__228;
 CHECK_BOUND( t_6, "R_228" )
 t_3 = CALL_2ARGS( t_4, t_5, t_6 );
 CHECK_FUNC_RESULT( t_3 )
 C_SUM_FIA( t_2, t_3, INTOBJ_INT(1) )
 CHECK_INT_POS( t_2 )
 C_ELM_LIST_FPL( t_1, a_list, t_2 )
 RES_BRK_CURR_STAT();
 SWITCH_TO_OLD_FRAME(oldFrame);
 return t_1;


 RES_BRK_CURR_STAT();
 SWITCH_TO_OLD_FRAME(oldFrame);
 return 0;
}
