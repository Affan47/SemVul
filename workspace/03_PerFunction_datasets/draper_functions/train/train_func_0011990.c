te_shutdown(void)
{
   DENTER(EVENT_LAYER, "te_shutdown");

   sge_free((char *)Handler_Tbl.list);

   DEXIT;
   return;
}
