iso9660_set_evd(void *pd)
{
  iso_volume_descriptor_t ied;

  cdio_assert (sizeof(iso_volume_descriptor_t) == ISO_BLOCKSIZE);

  cdio_assert (pd != NULL);

  memset(&ied, 0, sizeof(ied));

  ied.type = to_711(ISO_VD_END);
  iso9660_strncpy_pad (ied.id, ISO_STANDARD_ID, sizeof(ied.id),
                       ISO9660_DCHARS);
  ied.version = to_711(ISO_VERSION);

  memcpy(pd, &ied, sizeof(ied));
}
