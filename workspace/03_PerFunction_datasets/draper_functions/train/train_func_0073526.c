add_glarea_child(GtkWidget* winchild,gchar* title)
{
  if(GLArea)
  {
  	add_child(PrincipalWindow,winchild,gtk_widget_destroy,title);
  	g_signal_connect(G_OBJECT(winchild),"delete_event",(GCallback)delete_child,NULL);
  }
  else
  {
  	add_button_windows(title,winchild);
  	g_signal_connect(G_OBJECT(winchild), "delete_event",(GCallback)destroy_button_windows,NULL);
  	g_signal_connect(G_OBJECT(winchild), "delete_event",G_CALLBACK(gtk_widget_destroy),NULL);
  }
}
