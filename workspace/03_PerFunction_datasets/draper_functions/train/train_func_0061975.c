node_strcmp ( xmlNodePtr node, gchar * name )
{
  return node -> name && ! strcmp ( ( gchar *) node -> name, name );
}
