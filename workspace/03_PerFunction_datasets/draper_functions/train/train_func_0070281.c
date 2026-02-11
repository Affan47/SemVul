printPolygon(const Polygon &p)
{
  fprintf(Stderr,"{\n");
  for(Polygon::const_iterator i=p.begin();i!=p.end();i++)
    i->print();
  fprintf(Stderr,"}\n");
}
