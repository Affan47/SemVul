ServerAlias()
{
  static Dictionary *serveraliases= 0;

  if (_config && ! serveraliases)
    {
      String l= (*_config)["server_aliases"];
      String from, *to;
      serveraliases = new Dictionary();
      char *p = strtok(l, " \t");
      char *salias= NULL;
      while (p)
	{
	  salias = strchr(p, '=');
	  if (! salias)
	    {
	      p = strtok(0, " \t");
	      continue;
	    }
	  *salias++= '\0';
	  from = p;
	  if (from.indexOf(':') == -1)
	    from.append(":80");
	  to= new String(salias);
	  if (to->indexOf(':') == -1)
	    to->append(":80");
	  serveraliases->Add(from.get(), to);

	  p = strtok(0, " \t");
	}
    }

  String *al= 0;
  int newport;
  int delim;
  _signature = _host;
  _signature << ':' << _port;
  if ((al= (String *) serveraliases->Find(_signature)))
    {
      delim= al->indexOf(':');

      _host= al->sub(0,delim).get();
      sscanf((char*)al->sub(delim+1), "%d", &newport);
      _port= newport;

    }
}
