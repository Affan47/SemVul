gst_caps_subtract (const GstCaps * minuend, const GstCaps * subtrahend)
{
  guint i, j, sublen;
  GstStructure *min;
  GstStructure *sub;
  GstCaps *dest = NULL, *src;

  g_return_val_if_fail (minuend != NULL, NULL);
  g_return_val_if_fail (subtrahend != NULL, NULL);

  if (CAPS_IS_EMPTY (minuend) || CAPS_IS_ANY (subtrahend)) {
    return gst_caps_new_empty ();
  }
  if (CAPS_IS_EMPTY_SIMPLE (subtrahend))
    return gst_caps_copy (minuend);


  g_return_val_if_fail (!CAPS_IS_ANY (minuend), NULL);
  sublen = subtrahend->structs->len;
  g_assert (sublen > 0);

  src = gst_caps_copy (minuend);
  for (i = 0; i < sublen; i++) {
    guint srclen;

    sub = gst_caps_get_structure_unchecked (subtrahend, i);
    if (dest) {
      gst_caps_unref (src);
      src = dest;
    }
    dest = gst_caps_new_empty ();
    srclen = src->structs->len;
    for (j = 0; j < srclen; j++) {
      min = gst_caps_get_structure_unchecked (src, j);
      if (gst_structure_get_name_id (min) == gst_structure_get_name_id (sub)) {
        GSList *list;

        if (gst_caps_structure_subtract (&list, min, sub)) {
          GSList *walk;

          for (walk = list; walk; walk = g_slist_next (walk)) {
            gst_caps_append_structure_unchecked (dest,
                (GstStructure *) walk->data);
          }
          g_slist_free (list);
        } else {
          gst_caps_append_structure_unchecked (dest, gst_structure_copy (min));
        }
      } else {
        gst_caps_append_structure_unchecked (dest, gst_structure_copy (min));
      }
    }
    if (CAPS_IS_EMPTY_SIMPLE (dest)) {
      gst_caps_unref (src);
      return dest;
    }
  }

  gst_caps_unref (src);
  gst_caps_do_simplify (dest);
  return dest;
}
