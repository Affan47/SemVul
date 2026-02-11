saveAppArgs( QDataStream &ds)
{
   if (!s->parsed)
      s->parseAllArgs();


   s->removeArgs("qt");
   s->removeArgs("kde");
   s->removeArgs("kuniqueapp");

   ds << s->mCwd;

   uint count = s->argsList ? s->argsList->count() : 0;
   ds << count;

   if (!count) return;

   KCmdLineArgsList::Iterator args;
   for(args = s->argsList->begin(); args != s->argsList->end(); ++args)
   {
      ds << (*args)->d->id;
      (*args)->d->save(ds);
   }
}
