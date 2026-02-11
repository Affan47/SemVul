mxf_metadata_base_resolve (MXFMetadataBase * self, GHashTable * metadata)
{
  MXFMetadataBaseClass *klass;
  gboolean ret = TRUE;

  g_return_val_if_fail (MXF_IS_METADATA_BASE (self), FALSE);
  g_return_val_if_fail (metadata != NULL, FALSE);

  if (self->resolved == MXF_METADATA_BASE_RESOLVE_STATE_SUCCESS)
    return TRUE;
  else if (self->resolved != MXF_METADATA_BASE_RESOLVE_STATE_NONE)
    return FALSE;

  self->resolved = MXF_METADATA_BASE_RESOLVE_STATE_RUNNING;

  klass = MXF_METADATA_BASE_GET_CLASS (self);

  if (klass->resolve)
    ret = klass->resolve (self, metadata);

  self->resolved =
      (ret) ? MXF_METADATA_BASE_RESOLVE_STATE_SUCCESS :
      MXF_METADATA_BASE_RESOLVE_STATE_FAILURE;

  return ret;
}
