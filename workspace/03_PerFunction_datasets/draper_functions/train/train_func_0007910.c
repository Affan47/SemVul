get_lvm_field (const char *cmd, const char *field, const char *device)
{
  char *out;
  CLEANUP_FREE char *err = NULL;
  int r = command (&out, &err,
                   str_lvm, cmd,
                   "--unbuffered", "--noheadings", "-o", field,
                   device, NULL);
  if (r == -1) {
    reply_with_error ("%s: %s", device, err);
    free (out);
    return NULL;
  }

  trim (out);
  return out;
}
