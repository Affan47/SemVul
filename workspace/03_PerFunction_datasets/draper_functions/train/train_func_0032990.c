stp_list_parameters(const stp_vars_t *v, stp_parameter_type_t p_type)
{
  if (p_type >= STP_PARAMETER_TYPE_STRING_LIST &&
      p_type < STP_PARAMETER_TYPE_INVALID)
    {
      const stp_list_t *list = v->params[p_type];
      stp_string_list_t *answer = stp_string_list_create();
      const stp_list_item_t *li = stp_list_get_start(list);
      while (li)
	{
	  const value_t *val = (value_t *) stp_list_item_get_data(li);
	  stp_string_list_add_string(answer, val->name, val->name);
	  li = stp_list_item_next(li);
	}
      return answer;
    }
  return NULL;
}
