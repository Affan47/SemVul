init_wires(void)
{
 int32 ii;

 __wire_init = TRUE;


 __nchg_futend = __nchg_futhdr = NULL;
 __initalw_thrd_hdr = NULL;


 for (ii = 0; ii < __numtopm; ii++)
  {
   init_itinsts(__it_roots[ii]);


  }


 __init_all_trchans();

 __wire_init = FALSE;
 if (__ev_tracing)
  __tr_msg("\n>>>> wire initialization complete <<<<<\n");
}
