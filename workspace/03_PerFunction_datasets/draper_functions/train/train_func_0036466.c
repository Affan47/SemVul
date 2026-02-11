mx_style_sheet_get_properties (MxStyleSheet *sheet,
                               MxStylable   *node)
{
  GTimer *timer = NULL;
  GList *l, *matching_selectors = NULL;
  SelectorMatch *selector_match = NULL;
  GHashTable *result;

  if (_mx_debug (MX_DEBUG_CSS))
    {
      const char *id = clutter_actor_get_name (CLUTTER_ACTOR (node));
      const char *class = mx_stylable_get_style_class (node);
      const char *pseudo_class = mx_stylable_get_style_pseudo_class (node);
      const char *type_name = G_OBJECT_TYPE_NAME (node);

      timer = g_timer_new ();
      g_print ("\x1b[1m");
      MX_NOTE (CSS, "Matches for: %s%s%s%s%s%s%s",
               (type_name) ? type_name : "",
               (class) ? "." : "",
               (class) ? class : "",
               (id) ? "#" : "",
               (id) ? id : "",
               (pseudo_class) ? ":" : "",
               (pseudo_class) ? pseudo_class : "");
      g_print ("\x1b[22m");
    }


  for (l = sheet->selectors; l; l = l->next)
    {
      gint score;

      score = css_node_matches_selector (l->data, node);

      if (score >= 0)
        {
          selector_match = g_slice_new (SelectorMatch);
          selector_match->selector = l->data;
          selector_match->score = score;
          matching_selectors = g_list_prepend (matching_selectors,
                                               selector_match);
        }
    }


  matching_selectors = g_list_sort (matching_selectors,
                                    (GCompareFunc) compare_selector_matches);


  result = g_hash_table_new_full (g_str_hash,
                                  g_str_equal,
                                  NULL,
                                  (GDestroyNotify)mx_style_sheet_value_free);
  for (l = matching_selectors; l; l = l->next)
    {
      SelectorMatch *match = l->data;
      struct _css_table_copy_data copy_data;

      copy_data.filename = match->selector->filename;
      copy_data.table = result;

      g_hash_table_foreach (match->selector->style, (GHFunc) css_table_copy,
                            &copy_data);

      if (_mx_debug (MX_DEBUG_CSS))
        print_selector (match->selector, match->score);
    }

  g_list_foreach (matching_selectors, (GFunc) free_selector_match, NULL);
  g_list_free (matching_selectors);

  if (_mx_debug (MX_DEBUG_CSS))
    {
      g_print ("\x1b[2m");
      MX_NOTE (CSS, "%fs", g_timer_elapsed (timer, NULL));
      g_print ("\x1b[0m");
      g_timer_destroy (timer);
    }

  return result;
}
