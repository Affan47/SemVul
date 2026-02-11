m_tiles(GtkWidget *, cchar *)
{
   int    tiles_dialog_event(zdialog *zd, cchar *event);
   void * tiles_thread(void *);

   zfuncs::F1_help_topic = "tiles";

   EFtiles.funcname = "tiles";
   EFtiles.Farea = 2;
   EFtiles.threadfunc = tiles_thread;
   if (! edit_setup(EFtiles)) return;

   zdialog *zd = zdialog_new(ZTX("Simulate Tiles"),mWin,Bdone,Bcancel,null);
   EFtiles.zd = zd;

   zdialog_add_widget(zd,"hbox","hb1","dialog",0,"space=5");
   zdialog_add_widget(zd,"label","labt","hb1",ZTX("tile size"),"space=5");
   zdialog_add_widget(zd,"spin","size","hb1","1|99|1|5","space=5");
   zdialog_add_widget(zd,"button","apply","hb1",Bapply,"space=10");
   zdialog_add_widget(zd,"hbox","hb2","dialog",0,"space=5");
   zdialog_add_widget(zd,"label","labg","hb2",ZTX("tile gap"),"space=5");
   zdialog_add_widget(zd,"spin","gap","hb2","0|9|1|1","space=5");

   zdialog_help(zd,"tiles");
   zdialog_run(zd,tiles_dialog_event,"-10/20");

   tile_size = 5;
   tile_gap = 1;

   tile_pixmap = (uint16 *) zmalloc(E1ww*E1hh*6,"tiles");
   memset(tile_pixmap,0,E1ww*E1hh*6);

   return;
}
