obo_header_validate(OBOHeader *obo_header, const char *obo_filename,
                               GtError *err)
{
  gt_error_check(err);
  gt_assert(obo_header && obo_filename);

  if (!obo_header_get(obo_header, "format-version")) {
    gt_error_set(err, "the header of OBO-file \"%s\" does not contain "
              "\"format-version\" tag", obo_filename);
    return -1;
  }
  return 0;
}
