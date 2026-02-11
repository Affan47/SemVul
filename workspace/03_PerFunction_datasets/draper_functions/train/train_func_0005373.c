stp_set_curve_parameter(stp_vars_t *v, const char *parameter,
			const stp_curve_t *curve)
{
  stp_list_t *list = v->params[STP_PARAMETER_TYPE_CURVE];
  stp_list_item_t *item = stp_list_get_item_by_name(list, parameter);
  stp_deprintf(STP_DBG_VARS, "stp_set_curve_parameter(0x%p, %s)\n",
	       (const void *) v, parameter);
  if (curve)
    {
      value_t *val;
      if (item)
	{
	  val = (value_t *) stp_list_item_get_data(item);
	  if (val->active == STP_PARAMETER_DEFAULTED)
	    val->active = STP_PARAMETER_ACTIVE;
	  if (val->value.cval)
	    stp_curve_destroy(val->value.cval);
	}
      else
	{
	  val = stp_malloc(sizeof(value_t));
	  val->name = stp_strdup(parameter);
	  val->typ = STP_PARAMETER_TYPE_CURVE;
	  val->active = STP_PARAMETER_ACTIVE;
	  stp_list_item_create(list, NULL, val);
	}
      val->value.cval = stp_curve_create_copy(curve);
    }
  else if (item)
    stp_list_item_destroy(list, item);
  stp_set_verified(v, 0);
}
