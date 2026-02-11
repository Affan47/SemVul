create_new_key (char *key_string)
{
  Key *k;
  char *key_str, *command = NULL;

#ifdef DEBUG
  printf ("create_new_key\n");
#endif

  key_str = strtok (key_string, ":");
  if (key_str != NULL)
    command = strtok (NULL, "\n");

  if (key_str == NULL || command == NULL)
    return;

  if (strlen (key_str) < 4)
    return;

  if ((k = malloc (sizeof *k)) == NULL)
    return;
  k->next = key;
  key = k;

  k->modifier = 0;
  k->keycode = 0;

  if (key_str[0] == '*')
    k->modifier = k->modifier | ShiftMask;
  if (key_str[1] == '*')
    k->modifier = k->modifier | ControlMask;
  if (key_str[2] == '*')
    k->modifier = k->modifier | Mod1Mask;

  k->keycode = XKeysymToKeycode (dpy, XStringToKeysym (key_str + 3));

  grab_key (k->keycode, k->modifier, root);
  k->command = strdup (command);
  return;
}
