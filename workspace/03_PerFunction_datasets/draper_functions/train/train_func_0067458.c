gap_cme_gui_check_gui_thread_is_active(GapCmeGlobalParams *gpp)
{
   static gboolean l_gap_message_open = FALSE;

   if(gpp->val.gui_proc_thread)
   {


     if(gap_debug) printf("MASTER: GUI thread %d is already active\n", (int)gpp->val.gui_proc_thread);
     if(l_gap_message_open == FALSE)
     {
       l_gap_message_open = TRUE;
       p_gap_message(_("Encoder specific Parameter Window still open"));
       l_gap_message_open = FALSE;
     }
     return (TRUE);
   }
   return (FALSE);
}
