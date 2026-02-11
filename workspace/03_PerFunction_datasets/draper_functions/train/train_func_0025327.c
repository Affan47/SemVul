m_gallery2(int Nth, int button)
{
   char     *file;

   zfuncs::F1_help_topic = "navigation";

   if (Nth == -1) return;

   file = image_gallery(0,"find",Nth);
   if (! file) return;

   if (edit_coll_name && button == 3)
   {
      edit_coll_popmenu(null,file);
      zfree(file);
      return;
   }

   f_open(file,1,Nth);
   zfree(file);

   gtk_window_present(MWIN);
   return;
}
