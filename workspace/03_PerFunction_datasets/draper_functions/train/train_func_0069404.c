_finish(Evry_Plugin *plugin)
{
   GET_PLUGIN(p, plugin);

   IF_RELEASE(p->input);
   IF_RELEASE(p->directory);

   if (p->thread)
     p->waiting_to_finish = 1;

   _free_files(p);

   if (!p->waiting_to_finish)
     E_FREE(p);
}
