_td_check_sizeof (td_thragent_t *ta, uint32_t *sizep, int sizep_name)
{
  if (*sizep == 0)
    {
      psaddr_t descptr;
      ps_err_e err = td_lookup (ta->ph, sizep_name, &descptr);
      if (err == PS_NOSYM)
	return TD_NOCAPAB;
      if (err == PS_OK)
	err = ps_pdread (ta->ph, descptr, sizep, sizeof *sizep);
      if (err != PS_OK)
	return TD_ERR;
      if (*sizep & 0xff000000U)
	*sizep = bswap_32 (*sizep);
    }
  return TD_OK;
}
