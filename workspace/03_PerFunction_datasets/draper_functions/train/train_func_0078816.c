Destroy(Widget w)
#else
static void Destroy(w)
Widget w;
#endif
{
    XmtLayoutWidget lw = (XmtLayoutWidget) w;

#if XmVersion < 2000
    if (lw->layout.font_list) XmFontListFree(lw->layout.font_list);
#else
    if (lw->layout.render_table) XmRenderTableFree(lw->layout.render_table);
#endif

    XtReleaseGC(w, lw->layout.gc);
    XtReleaseGC(w, lw->layout.grey_gc);
}
