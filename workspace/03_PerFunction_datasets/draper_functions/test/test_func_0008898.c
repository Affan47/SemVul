traverseproto (global_State *g, Proto *f) {
  int i;
  if (f->cache && iswhite(f->cache))
    f->cache = NULL;
  markobject(g, f->source);
  for (i = 0; i < f->sizek; i++)
    markvalue(g, &f->k[i]);
  for (i = 0; i < f->sizeupvalues; i++)
    markobject(g, f->upvalues[i].name);
  for (i = 0; i < f->sizep; i++)
    markobject(g, f->p[i]);
  for (i = 0; i < f->sizelocvars; i++)
    markobject(g, f->locvars[i].varname);
  return sizeof(Proto) + sizeof(Instruction) * f->sizecode +
                         sizeof(Proto *) * f->sizep +
                         sizeof(TValue) * f->sizek +
                         sizeof(int) * f->sizelineinfo +
                         sizeof(LocVar) * f->sizelocvars +
                         sizeof(Upvaldesc) * f->sizeupvalues;
}
