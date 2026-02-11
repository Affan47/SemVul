dns_table_add_cname(dns_table_t* const table,
                        dns_cname_entry_t* const new_entry) {
  if (table->cname_length >= DNS_TABLE_CNAME_ENTRIES) {
    ++table->num_dropped_cname_entries;
    return -1;
  }
#ifndef DISABLE_ANONYMIZATION
  if (table->whitelist
      && (!domain_whitelist_lookup(table->whitelist, new_entry->domain_name)
        || !domain_whitelist_lookup(table->whitelist, new_entry->cname))) {
    new_entry->unanonymized = 1;
  } else {
    new_entry->unanonymized = 0;
  }
#endif
  table->cname_entries[table->cname_length] = *new_entry;
  ++table->cname_length;
  return 0;
}
