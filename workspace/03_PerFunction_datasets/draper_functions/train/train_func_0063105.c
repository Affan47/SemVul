mag_find_descr_from_token(const char* token)
{
  icon_mapping_t* i = icon_mapping;

  if (icon_mapping == NULL) {
    return "unknown";
  }

  for (i = icon_mapping; i->token; i++) {
    if (token[0] == 0) {
      break;
    }
    if (case_ignore_strcmp(token, i->token) == 0) {
      return i->icon;
    }
  }
  return icon_mapping[0].icon;
}
