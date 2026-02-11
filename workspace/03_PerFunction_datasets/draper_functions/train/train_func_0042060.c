set_raw_parameter(stp_list_t *list, const char *parameter, const char *value,
		  size_t bytes, int typ)
{
  stp_list_item_t *item = stp_list_get_item_by_name(list, parameter);
  if (value)
    {
      value_t *val;
      if (item)
	{
	  val = (value_t *) stp_list_item_get_data(item);
	  if (val->active == STP_PARAMETER_DEFAULTED)
	    val->active = STP_PARAMETER_ACTIVE;
	  stp_free(stpi_cast_safe(val->value.rval.data));
	}
      else
	{
	  val = stp_malloc(sizeof(value_t));
	  val->name = stp_strdup(parameter);
	  val->typ = typ;
	  val->active = STP_PARAMETER_ACTIVE;
	  stp_list_item_create(list, NULL, val);
	}
      copy_to_raw(&(val->value.rval), value, bytes);
    }
  else if (item)
    stp_list_item_destroy(list, item);
}
