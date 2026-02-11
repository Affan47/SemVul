namespaceCleanup ( void )
{
  if ( nNamespaces > 1 )
    {
      initialNamespace = namespaces[0];
      free(namespaces);
      namespaces = &initialNamespace;
      nNamespaces = 1;
    }
}
