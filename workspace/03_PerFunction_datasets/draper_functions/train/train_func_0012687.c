hide_bar (rp_screen *s)
{
  if (s->bar_is_raised)
    {
      s->bar_is_raised = 0;
      XUnmapWindow (dpy, s->bar_window);


      if (current_window())
	{
	  XUninstallColormap (dpy, s->def_cmap);
	  XInstallColormap (dpy, current_window()->colormap);
	}

      return 1;
    }

  return 0;
}
