output_diff(const datetime_t& current)
{
  value_t cur_bal;

  transaction_xdata(*last_xact).date = current;
  compute_total(cur_bal, details_t(*last_xact));
  cur_bal.round();
  transaction_xdata(*last_xact).date = 0;

  if (value_t diff = cur_bal - last_balance) {
    entry_temps.push_back(entry_t());
    entry_t& entry = entry_temps.back();
    entry.payee = "Commodities revalued";
    entry._date = current;

    handle_value(diff, NULL, &entry, TRANSACTION_NO_TOTAL, xact_temps,
		 *handler);
  }
}
