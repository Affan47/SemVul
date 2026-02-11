firstLineno()
{

  TraceLineMap* map = lineMap();

  if (!map || map->count() == 0) return 0;
  TraceLineMap::Iterator it = map->begin();
  return (*it).lineno();
}
