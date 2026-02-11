sanei_genesys_init_fe (Genesys_Device * dev)
{
  unsigned int i;

  DBGSTART;
  for (i = 0; i < sizeof (Wolfson) / sizeof (Genesys_Frontend); i++)
    {
      if (dev->model->dac_type == Wolfson[i].fe_id)
	{
	  memcpy (&dev->frontend, &Wolfson[i], sizeof (Genesys_Frontend));
	  return;
	}
    }
  DBG (DBG_error0,
       "sanei_genesys_init_fe: failed to find description for dac_type %d\n",
       dev->model->dac_type);
  DBG (DBG_info, "sanei_genesys_init_fe: dac_type %d set up\n",
       dev->model->dac_type);
  DBGCOMPLETED;
}
