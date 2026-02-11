stat_eval_ident(struct eval_state_t *es)
{
  struct stat_sdb_t *sdb = es->user_ptr;
  struct stat_stat_t *stat;
  static struct eval_value_t err_value = { et_int, { 0 } };
  struct eval_value_t val;


  for (stat = sdb->stats; stat != NULL; stat = stat->next)
    {
      if (!strcmp(stat->name, es->tok_buf))
	{

	  break;
	}
    }
  if (!stat)
    {

      eval_error = ERR_UNDEFVAR;
      return err_value;
    }


  switch (stat->sc)
    {
    case sc_int:
      val.type = et_int;
      val.value.as_int = *stat->variant.for_int.var;
      break;
    case sc_uint:
      val.type = et_uint;
      val.value.as_uint = *stat->variant.for_uint.var;
      break;
#ifdef HOST_HAS_QWORD
    case sc_qword:

      val.type = et_double;
#ifdef _MSC_VER
      val.value.as_double = (double)(sqword_t)*stat->variant.for_qword.var;
#else
      val.value.as_double = (double)*stat->variant.for_qword.var;
#endif
      break;
    case sc_sqword:

      val.type = et_double;
      val.value.as_double = (double)*stat->variant.for_sqword.var;
      break;
#endif
    case sc_float:
      val.type = et_float;
      val.value.as_float = *stat->variant.for_float.var;
      break;
    case sc_double:
      val.type = et_double;
      val.value.as_double = *stat->variant.for_double.var;
      break;
    case sc_dist:
    case sc_sdist:
      fatal("stat distributions not allowed in formula expressions");
      break;
    case sc_formula:
      {

	struct eval_state_t *es = eval_new(stat_eval_ident, sdb);
	char *endp;

	val = eval_expr(es, stat->variant.for_formula.formula, &endp);
	if (eval_error != ERR_NOERR || *endp != '\0')
	  {

	    val = err_value;
	  }

	eval_delete(es);
      }
      break;
    default:
      panic("bogus stat class");
    }

  return val;
}
