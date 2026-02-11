gss_inquire_cred_by_mech (OM_uint32 * minor_status,
			  const gss_cred_id_t cred_handle,
			  const gss_OID mech_type,
			  gss_name_t * name,
			  OM_uint32 * initiator_lifetime,
			  OM_uint32 * acceptor_lifetime,
			  gss_cred_usage_t * cred_usage)
{
  _gss_mech_api_t mech;
  gss_cred_id_t credh = cred_handle;
  OM_uint32 maj_stat;

  if (mech_type == GSS_C_NO_OID)
    {
      if (minor_status)
	*minor_status = 0;
      return GSS_S_BAD_MECH;
    }

  mech = _gss_find_mech (mech_type);
  if (mech == NULL)
    {
      if (minor_status)
	*minor_status = 0;
      return GSS_S_BAD_MECH;
    }

  if (cred_handle == GSS_C_NO_CREDENTIAL)
    {
      maj_stat = gss_acquire_cred (minor_status,
				   GSS_C_NO_NAME, GSS_C_INDEFINITE,


				   GSS_C_NO_OID_SET,
				   GSS_C_INITIATE, &credh, NULL, NULL);
      if (GSS_ERROR (maj_stat))
	return maj_stat;
    }

  maj_stat = mech->inquire_cred_by_mech (minor_status, credh, mech_type, name,
					 initiator_lifetime,
					 acceptor_lifetime, cred_usage);

  if (cred_handle == GSS_C_NO_CREDENTIAL)
    gss_release_cred (NULL, &credh);

  return maj_stat;
}
