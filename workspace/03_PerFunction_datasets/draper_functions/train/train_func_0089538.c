values_equal (GParamSpec *pspec,
              const GValue *va,
              const GValue *vb)
{


  if (g_param_values_cmp (pspec, va, vb) == 0)
    return TRUE;

  if (G_PARAM_SPEC_VALUE_TYPE (pspec) == GDK_TYPE_COLOR)
    return gdk_color_equal (g_value_get_boxed (va), g_value_get_boxed (vb));

  if (G_PARAM_SPEC_VALUE_TYPE (pspec) == PANGO_TYPE_FONT_DESCRIPTION)
    return pango_font_description_equal (g_value_get_boxed (va), g_value_get_boxed (vb));

  if (G_IS_PARAM_SPEC_VALUE_ARRAY (pspec) &&
      G_PARAM_SPEC_VALUE_TYPE (G_PARAM_SPEC_VALUE_ARRAY (pspec)->element_spec) == GDK_TYPE_COLOR)
    {
      GValueArray *ara, *arb;
      guint i;

      ara = g_value_get_boxed (va);
      arb = g_value_get_boxed (vb);

      if (!ara || !arb || ara->n_values != arb->n_values)
        return FALSE;

      for (i = 0; i < ara->n_values; ++i)
        if (!gdk_color_equal (g_value_get_boxed (g_value_array_get_nth (ara, i)),
                              g_value_get_boxed (g_value_array_get_nth (arb, i))))
          return FALSE;

      return TRUE;
    }

  return FALSE;
}
