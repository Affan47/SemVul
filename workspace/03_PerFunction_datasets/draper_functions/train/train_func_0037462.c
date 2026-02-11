create_file_bitmap (GVfsBackendAfp *afp_backend, GFileAttributeMatcher *matcher)
{
  guint16 file_bitmap;

  file_bitmap = create_filedir_bitmap (afp_backend, matcher);

  if (g_file_attribute_matcher_matches (matcher, G_FILE_ATTRIBUTE_STANDARD_SIZE))
    file_bitmap |= AFP_FILE_BITMAP_EXT_DATA_FORK_LEN_BIT;

  return file_bitmap;
}
