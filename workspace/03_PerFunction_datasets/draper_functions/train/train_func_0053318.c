gtr_po_set_location (GtrPo * po, GFile * location)
{
  g_return_if_fail (GTR_IS_PO (po));

  if (po->priv->location)
    {
      if (g_file_equal (po->priv->location, location))
        return;
      g_object_unref (po->priv->location);
    }

  po->priv->location = g_file_dup (location);

  g_object_notify (G_OBJECT (po), "location");
}
