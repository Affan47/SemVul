selector_to_string (MxSelector *selector)
{
  gchar *ancestor, *string, *tmp, *parent, *ret;

  if (!selector)
    return NULL;

  tmp = selector_to_string (selector->ancestor);
  if (tmp)
    ancestor = g_strconcat (tmp, " ", NULL);
  else
    ancestor = NULL;
  g_free (tmp);

  tmp = selector_to_string (selector->parent);
  if (tmp)
    parent = g_strconcat (tmp, " > ", NULL);
  else
    parent = NULL;
  g_free (tmp);

  string = g_strdup_printf ("%s%s%s%s%s%s%s",
                            (selector->type) ?  selector->type : "",
                            (selector->class) ? "." : "",
                            (selector->class) ? selector->class : "",
                            (selector->id) ? "#" : "",
                            (selector->id) ? selector->id : "",
                            (selector->pseudo_class) ? ":" : "",
                            (selector->pseudo_class)
                            ? selector->pseudo_class : "");

  ret = g_strconcat ((ancestor) ? ancestor : "",
                     (parent) ? parent : "",
                     string, NULL);

  g_free (string);

  g_free (ancestor);
  g_free (parent);

  return ret;
}
