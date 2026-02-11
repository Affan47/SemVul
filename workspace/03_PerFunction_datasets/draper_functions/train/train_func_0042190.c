server_option_free(struct server_option *poption)
{
  switch (poption->base_option.type) {
  case OT_STRING:
    if (NULL != poption->string.value) {
      FC_FREE(poption->string.value);
    }
    if (NULL != poption->string.def) {
      FC_FREE(poption->string.def);
    }
    break;

  case OT_ENUM:
    if (NULL != poption->enumerator.support_names) {
      strvec_destroy(poption->enumerator.support_names);
      poption->enumerator.support_names = NULL;
    }
    if (NULL != poption->enumerator.pretty_names) {
      strvec_destroy(poption->enumerator.pretty_names);
      poption->enumerator.pretty_names = NULL;
    }
    break;

  case OT_BITWISE:
    if (NULL != poption->bitwise.support_names) {
      strvec_destroy(poption->bitwise.support_names);
      poption->bitwise.support_names = NULL;
    }
    if (NULL != poption->bitwise.pretty_names) {
      strvec_destroy(poption->bitwise.pretty_names);
      poption->bitwise.pretty_names = NULL;
    }
    break;

  case OT_BOOLEAN:
  case OT_INTEGER:
  case OT_FONT:
  case OT_COLOR:
  case OT_VIDEO_MODE:
    break;
  }

  if (NULL != poption->name) {
    FC_FREE(poption->name);
  }
  if (NULL != poption->description) {
    FC_FREE(poption->description);
  }
  if (NULL != poption->help_text) {
    FC_FREE(poption->help_text);
  }
}
