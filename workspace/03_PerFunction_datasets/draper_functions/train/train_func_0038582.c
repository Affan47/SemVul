prepare(GtkWidget *w, GdkPixmap *t, GdkGC *gc, int a, int b, int c, int d) {
  int i;
  Target = t;
  GC = gc;
  X=a; Y=b, W=c; H=d;


  if (pl!=NULL)
    g_object_unref(G_OBJECT(pl));
  for(i=0;i<5;i++)
    if (pfd[i]!=NULL)
      pango_font_description_free(pfd[i]);

  for(i=0;i<5;i++)
    pfd[i] = NULL;

  pl = gtk_widget_create_pango_layout(w,NULL);
}
