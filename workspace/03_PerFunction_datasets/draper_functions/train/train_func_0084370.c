handle_commit_quad (fs_backend *be, fs_segment segment,
                                             unsigned int length,
                                             unsigned char *content)
{
  if (segment > be->segments) {
    fs_error(LOG_ERR, "invalid segment number: %d", segment);
    return fsp_error_new(segment, "invalid segment number");
  }

  if (length != sizeof(int)) {
    fs_error(LOG_ERR, "commit_quad(%d) missing flags", segment);
    return fsp_error_new(segment, "missing flags");
  }

  int flags;

  memcpy(&flags, content, sizeof (flags));
  int ret = fs_quad_import_commit(be, segment, flags, 1);
  if (ret) {
    fs_error(LOG_ERR, "commit_quad(%d) failed", segment);
    return fsp_error_new(segment, "quad commit failed");
  }

  return message_new(FS_DONE_OK, segment, 0);
}
