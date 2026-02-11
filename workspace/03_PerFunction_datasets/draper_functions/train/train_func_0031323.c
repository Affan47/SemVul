handle_start_import (fs_backend *be, fs_segment segment,
                                            unsigned int length,
                                            unsigned char *content)
{
  if (segment > be->segments) {
    fs_error(LOG_ERR, "invalid segment number: %d", segment);
    return fsp_error_new(segment, "invalid segment number");
  }

  if (length > 0) {
    fs_error(LOG_ERR, "start_import(%d) extraneous content", segment);
    return fsp_error_new(segment, "extraneous content");
  }

  float free_space = fs_free_disk(fs_backend_get_kb(be));
  if (free_space < be->min_free) {
    fs_error(LOG_ERR, "segment %d only has %.1f%% free space", segment, free_space);
    return fsp_error_new(segment, "low disk space");
  }

  fs_start_import(be, segment);

  return message_new(FS_DONE_OK, segment, 0);
}
