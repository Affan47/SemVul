userbutton_handler(void)
{
  Bit32u shortcut[4];
  Bit32u symbol;
  char user_shortcut[512];
  char *ptr;
  int i, len = 0, ret = 1;

  if (BX_GUI_THIS dialog_caps & BX_GUI_DLG_USER) {
    ret = SIM->ask_param(BXPN_USER_SHORTCUT);
  }
  strcpy(user_shortcut, SIM->get_param_string(BXPN_USER_SHORTCUT)->getptr());
  if ((ret > 0) && user_shortcut[0] && (strcmp(user_shortcut, "none"))) {
    ptr = strtok(user_shortcut, "-");
    if ((strcmp(ptr, SIM->get_param_string(BXPN_USER_SHORTCUT)->getptr())) ||
        (strlen(SIM->get_param_string(BXPN_USER_SHORTCUT)->getptr()) < 6)) {
      while (ptr) {
        symbol = get_user_key(ptr);
        if (symbol == BX_KEY_UNKNOWN) {
          BX_ERROR(("Unknown shortcut %s ignored", ptr));
          return;
        }
        shortcut[len++] = symbol;
        ptr = strtok(NULL, "-");
      }
    } else {
      BX_ERROR(("Unknown shortcut %s ignored", user_shortcut));
      return;
    }
    i = 0;
    while (i < len) {
      DEV_kbd_gen_scancode(shortcut[i++]);
    }
    i--;
    while (i >= 0) {
      DEV_kbd_gen_scancode(shortcut[i--] | BX_KEY_RELEASED);
    }
  }
}
