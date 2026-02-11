Initialize (
   Widget request_w,
   Widget new_w,
   ArgList args,
   Cardinal* num_args )
{
   Widget w;
   char tmpstr[256];
   XmpSpinboxWidget cw = (XmpSpinboxWidget)new_w;


   SpinboxOldValue(cw) = LONG_MAX;

   SpinboxContext(cw) = XtWidgetToApplicationContext(new_w);
   XtAppAddActions ( SpinboxContext(cw), actions, XtNumber(actions) );

   validate_new_type ( cw, SpinboxType(cw) );
   set_getshow_procs ( cw );


   if (!did_user_specify(XmNminimum,args,*num_args) &&
         SpinboxMinValue(cw)==LONG_MIN+1)
      set_default_min(cw);
   if (!did_user_specify(XmNmaximum,args,*num_args) &&
         SpinboxMaxValue(cw)==LONG_MAX-1)
      set_default_max(cw);
   if (!did_user_specify(XmNincrementLarge,args,*num_args) &&
               SpinboxIncLarge(cw)==0)
      set_default_inc_large(cw);
   if (!did_user_specify(XmNbuttonSizeRatio,args,*num_args))
      set_default_button_ratio(cw);


   validate_new_minimum(cw, SpinboxMinValue(cw));
   validate_new_maximum(cw, SpinboxMaxValue(cw));
   validate_new_inc_large(cw, SpinboxIncLarge(cw));
   validate_new_style(cw, SpinboxStyle(cw));


   (*SpinboxShowValue(cw))((Widget)cw, SpinboxShowValueData(cw),
                              SpinboxValue(cw), tmpstr, sizeof(tmpstr));
   SpinboxTF(cw) = XtVaCreateManagedWidget("tf", xmTextFieldWidgetClass, new_w,
      XmNvalue, tmpstr,
      XmNcolumns, SpinboxTFColumns(cw),
      NULL );
   set_tf_cb ( cw, True );
   XtOverrideTranslations ( SpinboxTF(cw), Translations );


   SpinboxUpBtn(cw) = w = XtVaCreateManagedWidget ( "up_ab",
                           xmArrowButtonWidgetClass, new_w,
                           NULL );
   XtAddCallback ( w, XmNactivateCallback,   up_activate_cb, (XtPointer)cw );
   XtAddCallback ( w, XmNarmCallback,        up_arm_cb,      (XtPointer)cw );
   XtAddCallback ( w, XmNdisarmCallback,     ab_disarm_cb,   (XtPointer)cw );


   SpinboxDownBtn(cw) = w = XtVaCreateManagedWidget ( "down_ab",
                              xmArrowButtonWidgetClass, new_w,
                              NULL );
   XtAddCallback ( w, XmNactivateCallback, down_activate_cb, (XtPointer)cw );
   XtAddCallback ( w, XmNarmCallback,      down_arm_cb,      (XtPointer)cw );
   XtAddCallback ( w, XmNdisarmCallback,   ab_disarm_cb,   (XtPointer)cw );

   set_arrow_orientation ( cw );
   if ( SpinboxSensitive(cw) )
      set_sensitive ( cw, True );


   XmpGeometryInitialize ( xmpSpinboxWidgetClass, request_w, new_w, args, num_args );
}
