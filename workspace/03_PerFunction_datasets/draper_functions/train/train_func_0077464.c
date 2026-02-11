sge_set_commit_required(void)
{
   DENTER(TOP_LAYER,"sge_set_commit_required");


   {
      GET_SPECIFIC(event_master_transaction_t, t_store, sge_event_master_init_transaction_store, Event_Master_Control.transaction_key, "t_store");
      if (t_store->is_transaction) {
         WARNING((SGE_EVENT, "attempting to open a new event master transaction, but we already have a transaction open"));
      } else {
         t_store->is_transaction = true;
      }
   }

   DRETURN_VOID;
}
