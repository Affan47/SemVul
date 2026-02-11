tag_cmp_by_line (gconstpointer a,
                 gconstpointer b,
                 gpointer      data)
{
  const TMTag  *t1 = a;
  const TMTag  *t2 = b;
  gint          direction = GPOINTER_TO_INT (data);
  gint          rv;

  if (t1->type & tm_tag_file_t || t2->type & tm_tag_file_t) {
    rv = 0;
  } else {
    if (t1->atts.entry.line > t2->atts.entry.line) {
      rv = +direction;
    } else if (t1->atts.entry.line < t2->atts.entry.line) {
      rv = -direction;
    } else {
      rv = 0;
    }
  }

  return rv;
}
