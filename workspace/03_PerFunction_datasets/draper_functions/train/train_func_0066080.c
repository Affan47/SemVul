m_batchrename(GtkWidget *, cchar *)
{
   int   batchrename_dialog_event(zdialog *zd, cchar *event);

   zdialog  *zd;

   if (zdrename) return;

   if (is_syncbusy()) return;
   if (mod_keep()) return;
   if (! menulock(1)) return;

   zfuncs::F1_help_topic = "batch_rename";

   zd = zdialog_new(ZTX("Batch Rename"),mWin,Bproceed,Bcancel,null);
   zdialog_add_widget(zd,"hbox","hb1","dialog",0,"space=5");
   zdialog_add_widget(zd,"button","files","hb1",Bselectfiles,"space=10");
   zdialog_add_widget(zd,"label","labcount","hb1",ZTX("%d files selected"),"space=10");
   zdialog_add_widget(zd,"hbox","hb2","dialog","space=5");
   zdialog_add_widget(zd,"label","lab2","hb2",ZTX("new base name"),"space=10");
   zdialog_add_widget(zd,"entry","basename","hb2");
   zdialog_add_widget(zd,"hbox","hb3","dialog",0,"space=5");
   zdialog_add_widget(zd,"label","lab31","hb3",ZTX("starting sequence"),"space=10");
   zdialog_add_widget(zd,"entry","sequence","hb3","100","scc=5");
   zdialog_add_widget(zd,"label","lab32","hb3",ZTX("increment"),"space=10");
   zdialog_add_widget(zd,"entry","increment","hb3","01","scc=3");

   batchrename_filelist = 0;
   batchrename_filecount = 0;

   zdialog_help(zd,"batch_rename");
   zdialog_run(zd,batchrename_dialog_event);
   zdialog_wait(zd);

   zdialog_free(zd);
   menulock(0);
   return;
}
