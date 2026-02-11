sge_get_sockets(const char* qualified_hostname, lList **lpp) {

   int sockets = 0;

   DENTER(TOP_LAYER, "sge_get_sockets");


   sockets = get_execd_amount_of_sockets();


   sge_add_int2load_report(lpp, LOAD_ATTR_SOCKETS, sockets, qualified_hostname);

   DRETURN(0);
}
