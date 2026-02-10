stp_set_boolean_parameter(stp_vars_t *v, const char *parameter, int ival)
{
  stp_list_t *list = v->params[STP_PARAMETER_TYPE_BOOLEAN];
  value_t *val;
  stp_list_item_t *item = stp_list_get_item_by_name(list, parameter);
  stp_deprintf(STP_DBG_VARS, "stp_set_boolean_parameter(0x%p, %s, %d)\n",
	       (const void *) v, parameter, ival);
  if (item)
    {
      val = (value_t *) stp_list_item_get_data(item);
      if (val->active == STP_PARAMETER_DEFAULTED)
	val->active = STP_PARAMETER_ACTIVE;
    }
  else
    {
      val = stp_malloc(sizeof(value_t));
      val->name = stp_strdup(parameter);
      val->typ = STP_PARAMETER_TYPE_BOOLEAN;
      val->active = STP_PARAMETER_ACTIVE;
      stp_list_item_create(list, NULL, val);
    }
  if (ival)
    val->value.ival = 1;
  else
    val->value.ival = 0;
  stp_set_verified(v, 0);
}
