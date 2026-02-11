create_glarea (void) {

  GtkWidget* glarea;

  int attrlist[] = {
    GDK_GL_RGBA,
    GDK_GL_DOUBLEBUFFER,
    GDK_GL_DEPTH_SIZE, 1,
    GDK_GL_NONE
  };

  if(gdk_gl_query() == FALSE) {
    g_print("OpenGL not supported!\n");
    return NULL;
  }

  if ((glarea = gtk_gl_area_new(attrlist)) == NULL) {
    g_print("Error creating GtkGLArea!\n");
    return NULL;
  }

  gtk_widget_set_events(GTK_WIDGET(glarea), GDK_EXPOSURE_MASK);

  gtk_signal_connect (GTK_OBJECT(glarea), "expose_event",
                      GTK_SIGNAL_FUNC(glarea_draw), NULL);

  gtk_signal_connect (GTK_OBJECT(glarea), "configure_event",
                      GTK_SIGNAL_FUNC(glarea_reshape), NULL);

  gtk_signal_connect (GTK_OBJECT(glarea), "realize",
                      GTK_SIGNAL_FUNC(glarea_init), NULL);

  gtk_signal_connect (GTK_OBJECT(glarea), "destroy",
                      GTK_SIGNAL_FUNC (glarea_destroy), NULL);

  gtk_widget_set_usize(GTK_WIDGET(glarea), 256, 256);

  return (glarea);

}
