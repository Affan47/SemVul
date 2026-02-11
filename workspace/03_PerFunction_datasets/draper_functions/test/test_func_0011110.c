slideshow_dialog_event(zdialog *zd, cchar *event)
{
   char     *pp;

   if (! strEqu(event,"browse")) return 0;
   pp = zgetfile1(ZTX("Select music file or playlist"),"open",ss_musicfile);
   if (! pp) return 0;
   zdialog_stuff(zd,"musicfile",pp);
   zfree(pp);
   return 0;
}
