gtimefunc(void *arg)
{
   static zdialog    *zdmessage = 0;
   int               syncfd;

   if (Wrepaint) {
      Wrepaint = 0;
      mwpaint1();
   }

   update_statusbar();

   if (Fslideshow) slideshow_next("timer");

   if (Ffuncbusy)
      paint_text(Dww/2-50,Dhh-20,"BUSY","monospace 10");

   if (threadmessage && ! zdmessage)
      zdmessage = zmessage_post(mWin,0,threadmessage);

   if (zdmessage && ! threadmessage)
      zdialog_free(zdmessage);

   if (zdmessage && zdmessage->sentinel != zdsentinel) {
      zdmessage = 0;
      threadmessage = 0;
   }

   syncfd = global_lock(fsync_lock);
   if (syncfd >= 0) {
      global_unlock(syncfd);
      if (Fsyncbusy) threadmessage = 0;
      Fsyncbusy = 0;
   }
   else Fsyncbusy = 1;

   return 1;
}
