_eio_dir_stat_find_heavy(void *data, Ecore_Thread *thread)
{
   Eio_File_Dir_Ls *async = data;

   async->ls.common.thread = thread;
   async->pack = NULL;
   async->start = ecore_time_get();

   _eio_file_recursiv_ls(thread, &async->ls.common,
                         (Eio_Filter_Direct_Cb) _eio_dir_stat_find_forward,
			 eina_file_stat_ls,
                         async, async->ls.directory);

   if (async->pack) ecore_thread_feedback(thread, async->pack);
   async->pack = NULL;
}
