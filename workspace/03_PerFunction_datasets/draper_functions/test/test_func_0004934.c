qinstance_x_on_subordinate(sge_gdi_ctx_class_t *ctx,
                           lListElem *this_elem, bool suspend,
                           bool send_event, monitoring_t *monitor)
{
   bool ret = true;
   u_long32 sos_counter;
   bool do_action;
   bool send_qinstance_signal;
   const char *hostname;
   const char *cqueue_name;
   const char *full_name;
   int signal;
   ev_event event;

   DENTER(TOP_LAYER, "qinstance_x_on_subordinate");


   sos_counter = lGetUlong(this_elem, QU_suspended_on_subordinate);
   if (suspend) {
      sos_counter++;
   } else {
      sos_counter--;
   }
   lSetUlong(this_elem, QU_suspended_on_subordinate, sos_counter);


   hostname = lGetHost(this_elem, QU_qhostname);
   cqueue_name = lGetString(this_elem, QU_qname);
   full_name = lGetString(this_elem, QU_full_name);
   send_qinstance_signal = (qinstance_state_is_manual_suspended(this_elem) ||
                            qinstance_state_is_cal_suspended(this_elem)) ? false : true;
   if (suspend) {
      do_action = (sos_counter == 1) ? true : false;
      signal = SGE_SIGSTOP;
      event = sgeE_QINSTANCE_SOS;
   } else {
      do_action = (sos_counter == 0) ? true : false;
      signal = SGE_SIGCONT;
      event = sgeE_QINSTANCE_USOS;
   }


   DPRINTF(("qinstance "SFQ" "SFN" "SFN" on subordinate\n", full_name,
            (do_action ? "" : "already"),
            (suspend ? "suspended" : "unsuspended")));
   if (do_action) {
      DPRINTF(("Due to other suspend states signal will %sbe delivered\n",
               send_qinstance_signal ? "NOT " : ""));
      if (send_qinstance_signal) {
         ret = (sge_signal_queue(ctx, signal, this_elem, NULL, NULL, monitor) == 0) ? true : false;
      }

      sge_qmaster_qinstance_state_set_susp_on_sub(this_elem, suspend);
      if (send_event) {
         sge_add_event(0, event, 0, 0, cqueue_name, hostname, NULL, NULL);
      }
      lListElem_clear_changed_info(this_elem);


      do_slotwise_x_on_subordinate_check(ctx, this_elem, (bool)!suspend, false, monitor);
   }
   DRETURN(ret);
}
