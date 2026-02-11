Find(const char * name)
{
   C_F0 r;
   ListOfTOfId::const_iterator i=tables_of_identifier.begin();
   for(;i!=tables_of_identifier.end();++i)
    {
      TableOfIdentifier * ti=*i;
      r = ti->Find(name);
      if (r.NotNull()) return r;
    }
    if(mpirank==0)
    cerr << " The Identifier " << name << " does not exist " << endl;
    CompileError();
    return r;
}
