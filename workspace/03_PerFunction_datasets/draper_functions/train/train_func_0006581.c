mxf_metadata_identification_to_structure (MXFMetadataBase * m)
{
  GstStructure *ret =
      MXF_METADATA_BASE_CLASS
      (mxf_metadata_identification_parent_class)->to_structure (m);
  MXFMetadataIdentification *self = MXF_METADATA_IDENTIFICATION (m);
  gchar str[48];

  if (!mxf_uuid_is_zero (&self->this_generation_uid)) {
    mxf_uuid_to_string (&self->this_generation_uid, str);
    gst_structure_id_set (ret, MXF_QUARK (THIS_GENERATION_UID), G_TYPE_STRING,
        str, NULL);
  }

  if (self->company_name)
    gst_structure_id_set (ret, MXF_QUARK (COMPANY_NAME), G_TYPE_STRING,
        self->company_name, NULL);

  if (self->product_name)
    gst_structure_id_set (ret, MXF_QUARK (PRODUCT_NAME), G_TYPE_STRING,
        self->product_name, NULL);

  if (self->product_version.major ||
      self->product_version.minor ||
      self->product_version.patch ||
      self->product_version.build || self->product_version.release) {
    g_snprintf (str, 48, "%u.%u.%u.%u.%u", self->product_version.major,
        self->product_version.minor,
        self->product_version.patch,
        self->product_version.build, self->product_version.release);
    gst_structure_id_set (ret, MXF_QUARK (PRODUCT_VERSION), G_TYPE_STRING, str,
        NULL);
  }

  if (self->version_string)
    gst_structure_id_set (ret, MXF_QUARK (VERSION_STRING), G_TYPE_STRING,
        self->version_string, NULL);

  if (!mxf_uuid_is_zero (&self->product_uid)) {
    mxf_uuid_to_string (&self->product_uid, str);
    gst_structure_id_set (ret, MXF_QUARK (PRODUCT_UID), G_TYPE_STRING, str,
        NULL);
  }

  if (!mxf_timestamp_is_unknown (&self->modification_date)) {
    mxf_timestamp_to_string (&self->modification_date, str);
    gst_structure_id_set (ret, MXF_QUARK (MODIFICATION_DATE), G_TYPE_STRING,
        str, NULL);
  }

  if (self->toolkit_version.major ||
      self->toolkit_version.minor ||
      self->toolkit_version.patch ||
      self->toolkit_version.build || self->toolkit_version.release) {
    g_snprintf (str, 48, "%u.%u.%u.%u.%u", self->toolkit_version.major,
        self->toolkit_version.minor,
        self->toolkit_version.patch,
        self->toolkit_version.build, self->toolkit_version.release);
    gst_structure_id_set (ret, MXF_QUARK (TOOLKIT_VERSION), G_TYPE_STRING, str,
        NULL);
  }

  if (self->platform)
    gst_structure_id_set (ret, MXF_QUARK (PLATFORM), G_TYPE_STRING,
        self->platform, NULL);

  return ret;
}
