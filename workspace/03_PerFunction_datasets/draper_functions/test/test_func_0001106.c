conn_init(EpmdVars *g)
{
  int nbytes = g->max_conn * sizeof(Connection);
  Connection *connections = (Connection *)malloc(nbytes);

  if (connections == NULL)
    {
      dbg_printf(g,0,"epmd: Insufficient memory");
#ifdef DONT_USE_MAIN
      free(g->argv);
#endif
      exit(1);
    }

  memzero(connections, nbytes);

  return connections;
}
