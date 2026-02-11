Fortran_handle_option_auto (struct gcc_options *opts ATTRIBUTE_UNUSED,
                           struct gcc_options *opts_set ATTRIBUTE_UNUSED,
                           size_t scode ATTRIBUTE_UNUSED, const char *arg ATTRIBUTE_UNUSED, int value ATTRIBUTE_UNUSED,
                           unsigned int lang_mask ATTRIBUTE_UNUSED, int kind ATTRIBUTE_UNUSED,
                           location_t loc ATTRIBUTE_UNUSED,
                           const struct cl_option_handlers *handlers ATTRIBUTE_UNUSED,
                           diagnostic_context *dc ATTRIBUTE_UNUSED)
{
  enum opt_code code = (enum opt_code) scode;

  switch (code)
    {
    case OPT_Wextra:
      if (!opts_set->x_warn_unused_parameter)
        handle_generated_option (opts, opts_set,
                                 OPT_Wunused_parameter, NULL, value,
                                 lang_mask, kind, loc, handlers, dc);
      break;

    default:
      break;
    }
  return true;
}
