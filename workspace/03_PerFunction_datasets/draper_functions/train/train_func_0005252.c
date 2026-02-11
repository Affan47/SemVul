td_ta_map_lwp2thr (const td_thragent_t *ta_arg,
		   lwpid_t lwpid, td_thrhandle_t *th)
{
  td_thragent_t *const ta = (td_thragent_t *) ta_arg;

  LOG ("td_ta_map_lwp2thr");


  if (! ta_ok (ta))
    return TD_BADTA;


  psaddr_t list;
  td_err_e err = DB_GET_SYMBOL (list, ta, __stack_user);
  if (err != TD_OK)
    return err;

  err = DB_GET_FIELD (list, ta, list, list_t, next, 0);
  if (err != TD_OK)
    return err;

  if (list == 0)
    {
      if (ps_getpid (ta->ph) != lwpid)
	return TD_ERR;
      th->th_ta_p = ta;
      th->th_unique = 0;
      return TD_OK;
    }

  return __td_ta_lookup_th_unique (ta_arg, lwpid, th);
}
