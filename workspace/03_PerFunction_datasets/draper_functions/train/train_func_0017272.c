mov_close_callback (GtkWidget *widget,
                    t_mov_gui_stuff *mgp)
{
  if(mgp)
  {
    mov_remove_timer(mgp);

    if(mgp->shell)
    {
      GtkWidget *l_shell;

      l_shell = mgp->shell;
      mgp->shell = NULL;


      gtk_widget_destroy (l_shell);
    }
  }

  gtk_main_quit ();
}
