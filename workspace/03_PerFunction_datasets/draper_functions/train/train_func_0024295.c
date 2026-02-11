peek_required_version (ParseInfo *info)
{
  if (info->required_versions)
    return GPOINTER_TO_INT (info->required_versions->data);
  else
    return info->format_version;
}
