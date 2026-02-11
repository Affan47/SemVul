vectorb_delete_els (vector_b *vecp, gint nels, gint *els)
{
  gint k;
  gint jto, jfrom;
  gint *keepers = g_malloc ((vecp->nels - nels) * sizeof (gint));
  gint nkeepers = find_keepers (vecp->nels, nels, els, keepers);

  if (nels > 0 && nkeepers > 0) {


    for (k=0; k<nkeepers; k++) {
      jto = k;
      jfrom = keepers[k];
      if (jto != jfrom)
        vecp->els[jto] = vecp->els[jfrom];
    }

    vecp->els = (gboolean *) g_realloc (vecp->els,
                                     nkeepers * sizeof (gboolean));
    vecp->nels = nkeepers;
  }
  g_free (keepers);
}
