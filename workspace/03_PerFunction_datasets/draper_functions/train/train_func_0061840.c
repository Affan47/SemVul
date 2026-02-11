mxf_is_d10_essence_track (const MXFMetadataTimelineTrack * track)
{
  guint i;

  g_return_val_if_fail (track != NULL, FALSE);

  if (track->parent.descriptor == NULL)
    return FALSE;

  for (i = 0; i < track->parent.n_descriptor; i++) {
    MXFMetadataFileDescriptor *d = track->parent.descriptor[i];
    MXFUL *key;

    if (!d)
      continue;

    key = &d->essence_container;

    if (mxf_is_generic_container_essence_container_label (key) &&
        key->u[12] == 0x02 && key->u[13] == 0x01 &&
        (key->u[14] >= 0x01 && key->u[14] <= 0x06) &&
        (key->u[15] == 0x01 || key->u[15] == 0x02))
      return TRUE;
  }

  return FALSE;
}
