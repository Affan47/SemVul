HdlrFunc35 (
 Obj  self,
 Obj  a_obj,
 Obj  a_filter,
 Obj  a_val )
{
 Obj t_1 = 0;
 Bag oldFrame;
 OLD_BRK_CURR_STAT


 SWITCH_TO_NEW_FRAME(self,0,0,oldFrame);
 REM_BRK_CURR_STAT();
 SET_BRK_CURR_STAT(0);


 CHECK_BOOL( a_val )
 t_1 = (Obj)(UInt)(a_val != False);
 if ( t_1 ) {


  t_1 = GF_SetFilterObj;
  CALL_2ARGS( t_1, a_obj, a_filter );

 }


 else {


  t_1 = GF_ResetFilterObj;
  CALL_2ARGS( t_1, a_obj, a_filter );

 }


 RES_BRK_CURR_STAT();
 SWITCH_TO_OLD_FRAME(oldFrame);
 return 0;


 RES_BRK_CURR_STAT();
 SWITCH_TO_OLD_FRAME(oldFrame);
 return 0;
}
