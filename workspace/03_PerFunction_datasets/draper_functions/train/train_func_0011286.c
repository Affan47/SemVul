show_choice(int choice){
  char *menu_strings[MENU_STR_NUM] = {
    "",
    "1.Volume.",
    "2.Location.",
    "3.Scroll Settings.",
    "4.Playback Settings.",
    "5.Log out.",
    "6.Exit Program"
  };

  if (choice > 0 && choice < MENU_STR_NUM){
    display_string(menu_strings[choice],NOT_BLOCKING);
  }

  return;
}
