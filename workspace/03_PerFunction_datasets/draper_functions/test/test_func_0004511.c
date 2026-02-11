report_budget_items(const datetime_t& moment)
{
  if (pending_xacts.size() == 0)
    return;

  bool reported;
  do {
    reported = false;
    for (pending_xacts_list::iterator i = pending_xacts.begin();
	 i != pending_xacts.end();
	 i++) {
      datetime_t& begin = (*i).first.begin;
      if (! begin) {
	(*i).first.start(moment);
	begin = (*i).first.begin;
      }

      if (begin < moment &&
	  (! (*i).first.end || begin < (*i).first.end)) {
	transaction_t& xact = *(*i).second;

	DEBUG_PRINT("ledger.walk.budget", "Reporting budget for "
		    << xact_account(xact)->fullname());
	DEBUG_PRINT_TIME("ledger.walk.budget", begin);
	DEBUG_PRINT_TIME("ledger.walk.budget", moment);

	entry_temps.push_back(entry_t());
	entry_t& entry = entry_temps.back();
	entry.payee = "Budget entry";
	entry._date = begin;

	xact_temps.push_back(xact);
	transaction_t& temp = xact_temps.back();
	temp.entry   = &entry;
	temp.flags  |= TRANSACTION_AUTO | TRANSACTION_BULK_ALLOC;
	temp.amount.negate();
	entry.add_transaction(&temp);

	begin = (*i).first.increment(begin);

	item_handler<transaction_t>::operator()(temp);

	reported = true;
      }
    }
  } while (reported);
}
