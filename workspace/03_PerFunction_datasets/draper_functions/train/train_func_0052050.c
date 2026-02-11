parse_alpha (const char             *str,
             MetaAlphaGradientSpec **spec_ret,
             GMarkupParseContext    *context,
             GError                **error)
{
  char **split;
  int i;
  int n_alphas;
  MetaAlphaGradientSpec *spec;

  *spec_ret = NULL;

  split = g_strsplit (str, ":", -1);

  i = 0;
  while (split[i])
    ++i;

  if (i == 0)
    {
      set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                 _("Could not parse \"%s\" as a floating point number"),
                 str);

      g_strfreev (split);

      return FALSE;
    }

  n_alphas = i;


  spec = meta_alpha_gradient_spec_new (META_GRADIENT_HORIZONTAL,
                                       n_alphas);

  i = 0;
  while (i < n_alphas)
    {
      double v;

      if (!parse_double (split[i], &v, context, error))
        {

          g_strfreev (split);
          meta_alpha_gradient_spec_free (spec);

          return FALSE;
        }

      if (v < (0.0 - 1e-6) || v > (1.0 + 1e-6))
        {
          set_error (error, context, G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                     _("Alpha must be between 0.0 (invisible) and 1.0 (fully opaque), was %g\n"),
                     v);

          g_strfreev (split);
          meta_alpha_gradient_spec_free (spec);

          return FALSE;
        }

      spec->alphas[i] = (unsigned char) (v * 255);

      ++i;
    }

  g_strfreev (split);

  *spec_ret = spec;

  return TRUE;
}
