gss_compare_name (OM_uint32 * minor_status,
		  const gss_name_t name1,
		  const gss_name_t name2, int *name_equal)
{
  if (minor_status)
    *minor_status = 0;

  if (!name1 || !name2)
    return GSS_S_BAD_NAME | GSS_S_CALL_INACCESSIBLE_READ;

  if (!gss_oid_equal (name1->type, name2->type))
    return GSS_S_BAD_NAMETYPE;

  if (name_equal)
    *name_equal = (name1->length == name2->length) &&
      memcmp (name1->value, name2->value, name1->length) == 0;

  return GSS_S_COMPLETE;
}
