stop_search() {

   if (Init && Uci->searching) {

      ASSERT(Uci->searching);
      ASSERT(Uci->pending_nb>=1);

      my_log("POLYGLOT STOP SEARCH\n");


      if (option_get_bool("SyncStop")) {
         uci_send_stop_sync(Uci);
      } else {
         uci_send_stop(Uci);
      }
   }
}
