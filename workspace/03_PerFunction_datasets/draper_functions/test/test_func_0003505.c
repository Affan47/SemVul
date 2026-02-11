_create_ka_engine( PKA_ENGINE_PARMS* pp_engine )
{
  if( pp_engine == NULL  ||  *pp_engine != NULL )
  {

    return KA_INVALID_PARMS;
  }

  *pp_engine = (PKA_ENGINE_PARMS)pal_malloc( sizeof(KA_ENGINE_PARMS) );
  if( *pp_engine == NULL )
  {

    return KA_RESOURCE_STARVATION;
  }


  (*pp_engine)->ka_thread_id = 0;
  (*pp_engine)->ka_status = KA_STAT_INVALID;
  (*pp_engine)->p_echo_engine = NULL;


  return KA_PRIV_SUCCESS;
}
