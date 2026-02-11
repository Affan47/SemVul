do_apply_event(Relay_log_info const *rli)
{
  Item *it= 0;
  CHARSET_INFO *charset;
  query_id_t sav_query_id= 0;

  if (rli->deferred_events_collecting)
  {
    set_deferred(current_thd->query_id);
    return rli->deferred_events->add(this);
  } else if (is_deferred())
  {
    sav_query_id= current_thd->query_id;
    current_thd->query_id= query_id;
  }

  if (!(charset= get_charset(charset_number, MYF(MY_WME))))
    return 1;
  LEX_STRING user_var_name;
  user_var_name.str= name;
  user_var_name.length= name_len;
  double real_val;
  longlong int_val;


  const_cast<Relay_log_info*>(rli)->set_flag(Relay_log_info::IN_STMT);

  if (is_null)
  {
    it= new Item_null();
  }
  else
  {
    switch (type) {
    case REAL_RESULT:
      float8get(real_val, val);
      it= new Item_float(real_val, 0);
      val= (char*) &real_val;
      val_len= 8;
      break;
    case INT_RESULT:
      int_val= (longlong) uint8korr(val);
      it= new Item_int(int_val);
      val= (char*) &int_val;
      val_len= 8;
      break;
    case DECIMAL_RESULT:
    {
      Item_decimal *dec= new Item_decimal((uchar*) val+2, val[0], val[1]);
      it= dec;
      val= (char *)dec->val_decimal(NULL);
      val_len= sizeof(my_decimal);
      break;
    }
    case STRING_RESULT:
      it= new Item_string(val, val_len, charset);
      break;
    case ROW_RESULT:
    default:
      DBUG_ASSERT(1);
      return 0;
    }
  }

  Item_func_set_user_var *e=
    new Item_func_set_user_var(user_var_name, it, false);


  if (e->fix_fields(thd, 0))
    return 1;


  e->update_hash(val, val_len, type, charset, DERIVATION_IMPLICIT,
                 (flags & User_var_log_event::UNSIGNED_F));
  if (!is_deferred())
    free_root(thd->mem_root, 0);
  else
    current_thd->query_id= sav_query_id;

  return 0;
}
