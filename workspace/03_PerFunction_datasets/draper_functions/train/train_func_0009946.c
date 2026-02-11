gss_canonicalize_name (OM_uint32 * minor_status,
		       const gss_name_t input_name,
		       const gss_OID mech_type, gss_name_t * output_name)
{
  _gss_mech_api_t mech;

  mech = _gss_find_mech (mech_type);
  if (mech == NULL)
    {
      if (minor_status)
	*minor_status = 0;
      return GSS_S_BAD_MECH;
    }

  return mech->canonicalize_name (minor_status, input_name,
				  mech_type, output_name);
}
