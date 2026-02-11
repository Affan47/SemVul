iconsel_exts_add_clicked(GtkWidget *button,
                                     icon_selection_t *iconsel)
{
  file_ext_t *ext;
  g_assert((button != NULL) && (iconsel != NULL));
  TRACE("%s", "");
  if (file_ext_list_find(iconsel->apwal->iconsel_pref->file_exts, "") == NULL)
  {
    TRACE("%s", "add empty file_ext");
    ext = file_ext_new(g_strdup(""), TRUE);
    iconsel->apwal->iconsel_pref->file_exts = g_list_append(iconsel->apwal->iconsel_pref->file_exts, ext);
    icon_list_reload_all_with_splash(iconsel->icons);
    iconsel_refresh(iconsel);
  }
}
