m_warp_area(GtkWidget *, cchar *)
{
   int      WarpA_dialog_event(zdialog *zd, cchar *event);

   cchar  *WarpA_message = ZTX(
             " Select an area to warp using select area function. \n"
             " Press [start warp] and pull area with mouse. \n"
             " Make multiple mouse pulls until satisfied. \n"
             " When finished, select another area or press [done].");

   zfuncs::F1_help_topic = "warp_area";

   EFwarpA.funcname = "warp-area";
   EFwarpA.Farea = 2;
   EFwarpA.mousefunc = WarpA_mousefunc;
   if (! edit_setup(EFwarpA)) return;

   zdialog *zd = zdialog_new(ZTX("Warp Image (area)"),mWin,Bdone,Bcancel,null);
   EFwarpA.zd = zd;

   zdialog_add_widget(zd,"label","lab1","dialog",WarpA_message,"space=5");
   zdialog_add_widget(zd,"hbox","hb1","dialog",0,"space=5");
   zdialog_add_widget(zd,"button","start","hb1",ZTX("start warp"),"space=5");
   zdialog_add_widget(zd,"button","undolast","hb1",Bundolast,"space=5");
   zdialog_add_widget(zd,"button","undoall","hb1",Bundoall,"space=5");

   zdialog_help(zd,"warp_area");
   zdialog_run(zd,WarpA_dialog_event,"save");

   WarpAx = (float *) zmalloc(E3ww * E3hh * sizeof(float),"warpA");
   WarpAy = (float *) zmalloc(E3ww * E3hh * sizeof(float),"warpA");

   WarpA_init();

   return;
}
