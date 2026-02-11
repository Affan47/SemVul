qmonSubmitClear(Widget w, XtPointer cld, XtPointer cad)
{

   const char *qualified_hostname = ctx->get_qualified_hostname(ctx);

   DENTER(GUI_LAYER, "qmonSubmitClear");


   qmonFreeSMData(&SMData);
   qmonInitSMData(&SMData);

   XmtDialogSetDialogValues(submit_layout, &SMData);


   if (!ISSET(submit_mode_data.sub_mode, SUBMIT_QSH)) {
      XtSetSensitive(submit_stderror, True);
      XtSetSensitive(submit_stderrorPB, True);
   } else {
      char buf[512];
      String dsp = NULL;

      XmtInputFieldSetString(submit_name, "INTERACTIVE");
      dsp = DisplayString(XtDisplay(w));
      if (!strcmp(dsp, ":0") || !strcmp(dsp, ":0.0"))
         sprintf(buf, "DISPLAY=%s%s", qualified_hostname, dsp);
      else
         sprintf(buf, "DISPLAY=%s", dsp);
      XmtInputFieldSetString(submit_env, buf);
      XmToggleButtonSetState(submit_now, 1, True);
   }


   qmonSubmitChangeResourcesPixmap();


   XmtMsgLineClear(submit_message, XmtMsgLineNow);

   DEXIT;
}
