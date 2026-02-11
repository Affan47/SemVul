m_email(GtkWidget *, cchar *)
{
   int   email_dialog_event(zdialog *zd, cchar *event);

   zdialog     *zd;

   zfuncs::F1_help_topic = "e-mail";

   if (is_syncbusy()) return;
   if (mod_keep()) return;
   if (! menulock(1)) return;


   zd = zdialog_new(ZTX("E-mail Images"),mWin,Bproceed,Bcancel,null);
   zdialog_add_widget(zd,"hbox","hbf","dialog",0,"space=5");
   zdialog_add_widget(zd,"button","files","hbf",Bselectfiles,"space=5");
   zdialog_add_widget(zd,"label","fcount","hbf",ZTX("0 files selected"),"space=10");
   zdialog_add_widget(zd,"hbox","hbwh","dialog","space=10");
   zdialog_add_widget(zd,"vbox","vbwh1","hbwh",0,"homog|space=5");
   zdialog_add_widget(zd,"vbox","vbwh2","hbwh",0,"homog|space=5");
   zdialog_add_widget(zd,"label","labw","vbwh1",ZTX("max. width"));
   zdialog_add_widget(zd,"label","labh","vbwh1",ZTX("max. height"));
   zdialog_add_widget(zd,"entry","maxw","vbwh2","1000","scc=5");
   zdialog_add_widget(zd,"entry","maxh","vbwh2","700","scc=5");

   zdialog_stuff(zd,"maxw",emailsize[0]);
   zdialog_stuff(zd,"maxh",emailsize[1]);

   zdialog_help(zd,"e-mail");
   zdialog_run(zd,email_dialog_event);
   zdialog_wait(zd);

   menulock(0);
   return;
}
