cleanEdgePoint (gpointer data, gpointer userData)
{
  DatadEndpoints *el = (DatadEndpoints *) data;
  if (el && el->endpoints) {
    g_free (el->endpoints);
  }
}
