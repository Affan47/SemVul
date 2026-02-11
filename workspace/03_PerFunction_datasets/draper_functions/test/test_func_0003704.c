insert_tranx_node(const char *log_file_name,
				   my_off_t log_file_pos)
{
  const char *kWho = "ActiveTranx:insert_tranx_node";
  TranxNode  *ins_node;
  int         result = 0;
  unsigned int        hash_val;

  function_enter(kWho);

  ins_node = allocator_.allocate_node();
  if (!ins_node)
  {
    sql_print_error("%s: transaction node allocation failed for: (%s, %lu)",
                    kWho, log_file_name, (unsigned long)log_file_pos);
    result = -1;
    goto l_end;
  }


  strncpy(ins_node->log_name_, log_file_name, FN_REFLEN-1);
  ins_node->log_name_[FN_REFLEN-1] = 0;
  ins_node->log_pos_ = log_file_pos;

  if (!trx_front_)
  {

    trx_front_ = trx_rear_ = ins_node;
  }
  else
  {
    int cmp = compare(ins_node, trx_rear_);
    if (cmp > 0)
    {


      trx_rear_->next_ = ins_node;
      trx_rear_        = ins_node;
    }
    else
    {


      sql_print_error("%s: binlog write out-of-order, tail (%s, %lu), "
                      "new node (%s, %lu)", kWho,
                      trx_rear_->log_name_, (unsigned long)trx_rear_->log_pos_,
                      ins_node->log_name_, (unsigned long)ins_node->log_pos_);
      result = -1;
      goto l_end;
    }
  }

  hash_val = get_hash_value(ins_node->log_name_, ins_node->log_pos_);
  ins_node->hash_next_ = trx_htb_[hash_val];
  trx_htb_[hash_val]   = ins_node;

  if (trace_level_ & kTraceDetail)
    sql_print_information("%s: insert (%s, %lu) in entry(%u)", kWho,
                          ins_node->log_name_, (unsigned long)ins_node->log_pos_,
                          hash_val);

 l_end:
  return function_exit(kWho, result);
}
