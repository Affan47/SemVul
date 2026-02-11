operator()(transaction_t& xact)
{
  entry_temps.push_back(*xact.entry);
  entry_t& entry = entry_temps.back();
  entry._date = xact.date();
  entry.code  = xact.entry->code;

  if (xact.amount.commodity())
    entry.payee = xact.amount.commodity().symbol();
  else
    entry.payee = "<none>";

  xact_temps.push_back(xact);
  transaction_t& temp = xact_temps.back();
  temp.entry = &entry;
  temp.state = xact.state;
  temp.flags |= TRANSACTION_BULK_ALLOC;

  entry.add_transaction(&temp);

  item_handler<transaction_t>::operator()(temp);
}
