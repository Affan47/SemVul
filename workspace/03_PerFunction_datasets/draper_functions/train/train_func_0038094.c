handle_server_setting_str
    (const struct packet_server_setting_str *packet)
{
  struct option *poption = server_optset_option_by_number(packet->id);
  struct server_option *psoption = SERVER_OPTION(poption);
  bool need_gui_remove = FALSE;
  bool need_gui_add = FALSE;

  fc_assert_ret(NULL != poption);

  if (NULL == poption->common_vtable) {

    poption->poptset = server_optset;
    poption->common_vtable = &server_option_common_vtable;
    poption->type = OT_STRING;
    poption->str_vtable = &server_option_str_vtable;
  }
  fc_assert_ret_msg(OT_STRING == poption->type,
                    "Server setting \"%s\" (nb %d) has type %s (%d), "
                    "expected %s (%d)",
                    option_name(poption), option_number(poption),
                    option_type_name(poption->type), poption->type,
                    option_type_name(OT_STRING), OT_STRING);

  if (packet->is_visible) {
    if (NULL == psoption->string.value) {
      psoption->string.value = fc_strdup(packet->val);
    } else if (0 != strcmp(packet->val, psoption->string.value)) {
      free(psoption->string.value);
      psoption->string.value = fc_strdup(packet->val);
    }
    if (NULL == psoption->string.def) {
      psoption->string.def = fc_strdup(packet->default_val);
    } else if (0 != strcmp(packet->default_val, psoption->string.def)) {
      free(psoption->string.def);
      psoption->string.def = fc_strdup(packet->default_val);
    }
  }

  handle_server_setting_common(psoption, packet);
}
