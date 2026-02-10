_ar_card_theme_info_collate (const ArCardThemeInfo *a,
                                const ArCardThemeInfo *b)
{
  g_return_val_if_fail (a != NULL && b != NULL, 0);

  if (a->type != b->type)
    return theme_type_compare (a->type, b->type);

  return g_utf8_collate (a->display_name, b->display_name);
}
