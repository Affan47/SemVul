contact_pair_free (gpointer p)
{
  ContactPair *pair = p;

  g_object_unref (pair->contacts[0]);
  g_object_unref (pair->contacts[1]);
  g_slice_free (ContactPair, pair);
}
