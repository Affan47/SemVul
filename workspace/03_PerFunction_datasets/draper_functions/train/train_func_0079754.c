garcon_menu_directory_get_visible (GarconMenuDirectory *directory)
{
  g_return_val_if_fail (GARCON_IS_MENU_DIRECTORY (directory), FALSE);

  if (!garcon_menu_directory_get_show_in_environment (directory))
    return FALSE;
  else if (garcon_menu_directory_get_hidden (directory))
    return FALSE;
  else if (garcon_menu_directory_get_no_display (directory))
    return FALSE;

  return TRUE;
}
