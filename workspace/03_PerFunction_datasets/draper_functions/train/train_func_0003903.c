gst_registry_binary_check_magic (gchar ** in, gsize size)
{
  GstBinaryRegistryMagic *m;

  align (*in);
  GST_DEBUG ("Reading/casting for GstBinaryRegistryMagic at address %p", *in);
  unpack_element (*in, m, GstBinaryRegistryMagic, (*in + size), fail);

  if (strncmp (m->magic, GST_MAGIC_BINARY_REGISTRY_STR,
          GST_MAGIC_BINARY_REGISTRY_LEN) != 0) {
    GST_WARNING
        ("Binary registry magic is different : %02x%02x%02x%02x != %02x%02x%02x%02x",
        GST_MAGIC_BINARY_REGISTRY_STR[0] & 0xff,
        GST_MAGIC_BINARY_REGISTRY_STR[1] & 0xff,
        GST_MAGIC_BINARY_REGISTRY_STR[2] & 0xff,
        GST_MAGIC_BINARY_REGISTRY_STR[3] & 0xff, m->magic[0] & 0xff,
        m->magic[1] & 0xff, m->magic[2] & 0xff, m->magic[3] & 0xff);
    return -1;
  }
  if (strncmp (m->version, GST_MAGIC_BINARY_VERSION_STR,
          GST_MAGIC_BINARY_VERSION_LEN)) {
    GST_WARNING ("Binary registry magic version is different : %s != %s",
        GST_MAGIC_BINARY_VERSION_STR, m->version);
    return -2;
  }

  return 0;

fail:
  GST_WARNING ("Not enough data for binary registry magic structure");
  return -1;
}
