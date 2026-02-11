disp_init(int *argc, char *argv[], int color)
{
   Arg       wargs[2];
   XGCValues gcv;


   toplevel = XtInitialize(argv[0], "Coolmail", NULL, 0, argc, argv);

   disp_config();


   XtSetArg(wargs[0], XtNwidth,  (Dimension) DEFAULT_GFX_WIDTH);
   XtSetArg(wargs[1], XtNheight, (Dimension) DEFAULT_GFX_HEIGHT);


   main_gfx_w = XtCreateManagedWidget("picture",
                                     widgetClass,
                                     toplevel, wargs, 2);


   XtRealizeWidget(toplevel);


   disp_getsize(&Gfx_Width, &Gfx_Height);


   disp_setsize(Gfx_Width, Gfx_Height);


   if(color == 0) color_mode = 0;
   init_colors(XtDisplay(main_gfx_w), color_table, color_mode);


   main_gfx_gc = XCreateGC(XtDisplay(main_gfx_w),
                           XtWindow(main_gfx_w), 0, &gcv);
   XSetFillRule(XtDisplay(main_gfx_w), main_gfx_gc, EvenOddRule);


   XtAddEventHandler(main_gfx_w, ExposureMask, FALSE,
                     (XtEventHandler)disp_expose_handler, NULL);
   XtAddEventHandler(main_gfx_w, StructureNotifyMask, FALSE,
                     (XtEventHandler)disp_config_handler, NULL);
   XtAddEventHandler(main_gfx_w, ButtonPressMask, FALSE,
                     (XtEventHandler)disp_select_handler, NULL);
   XtAddEventHandler(main_gfx_w, NoEventMask, True,
                     (XtEventHandler)disp_nomask_handler, NULL);
   xa_timeout = XInternAtom(XtDisplay(main_gfx_w), timeout_property, FALSE);
}
