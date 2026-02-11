gth_input_preprocess(GthInput *input,
                         bool gthconsensus,
                         bool noautoindex,
                         bool createindicesonly,
                         bool skipindexcheck,
                         bool maskpolyAtails,
                         bool online,
                         bool inverse,
                         const char *progname,
                         char *scorematrixfile,
                         unsigned int translationtable,
                         GthDuplicateCheck duplicate_check,
                         GthOutput *out, GtError *err)
{
  int had_err;
  gt_error_check(err);
  gt_assert(input);
  had_err = input->file_preprocessor(input, gthconsensus, noautoindex,
                                     skipindexcheck, maskpolyAtails, online,
                                     inverse, progname, translationtable, out,
                                     err);
  if (!had_err)
    had_err = gth_input_load_scorematrix(input, scorematrixfile, out, err);
  if (!had_err) {
    input->md5ids = out->md5ids;
    input->use_md5_cache = out->md5ids || duplicate_check == GTH_DC_SEQ ||
                           duplicate_check == GTH_DC_BOTH;
    input->use_desc_cache = duplicate_check == GTH_DC_DESC ||
                            duplicate_check == GTH_DC_BOTH;
  }
  if (!had_err && input->use_md5_cache && createindicesonly) {


    create_md5_cache_files(input);
  }
  return had_err;
}
