init_mechlist()
{
  cmechlist->utils=_sasl_alloc_utils(NULL, &global_callbacks_client);
  if (cmechlist->utils==NULL)
    return SASL_NOMEM;

  cmechlist->mech_list=NULL;
  cmechlist->mech_length=0;

  return SASL_OK;
}
