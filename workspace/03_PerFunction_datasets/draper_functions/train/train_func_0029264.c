set_filter_value(const char *value)
{
  bool status= true;

  switch (opt_id) {
  case OPT_REPLICATE_DO_DB:
    status= rpl_filter->set_do_db(value);
    break;
  case OPT_REPLICATE_DO_TABLE:
    status= rpl_filter->set_do_table(value);
    break;
  case OPT_REPLICATE_IGNORE_DB:
    status= rpl_filter->set_ignore_db(value);
    break;
  case OPT_REPLICATE_IGNORE_TABLE:
    status= rpl_filter->set_ignore_table(value);
    break;
  case OPT_REPLICATE_WILD_DO_TABLE:
    status= rpl_filter->set_wild_do_table(value);
    break;
  case OPT_REPLICATE_WILD_IGNORE_TABLE:
    status= rpl_filter->set_wild_ignore_table(value);
    break;
  }

  return status;
}
