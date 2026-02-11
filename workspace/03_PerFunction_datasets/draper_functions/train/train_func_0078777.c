desc_dec_config_descriptor_get_size (DecoderConfigDescriptor * dec_desc)
{
  guint64 size = 0;
  guint64 extra_size = 0;

  size += desc_base_descriptor_get_size (&dec_desc->base);

  extra_size += sizeof (guint8);

  extra_size += sizeof (guint8);

  extra_size += sizeof (guint8) * 3;

  extra_size += sizeof (guint32);

  extra_size += sizeof (guint32);
  if (dec_desc->dec_specific_info) {
    extra_size += desc_dec_specific_info_get_size (dec_desc->dec_specific_info);
  }

  desc_base_descriptor_set_size (&dec_desc->base, extra_size);
  return size + extra_size;
}
