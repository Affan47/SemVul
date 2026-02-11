used_stes() const
{
  stecoll *l = left     ? left->used_stes()     : new stecoll;
  stecoll *o = origin   ? new stecoll(origin)   : new stecoll;
  stecoll *a = arrayref ? arrayref->used_stes() : new stecoll;


  l->append(o);
  l->append(a);

  return l;
}
