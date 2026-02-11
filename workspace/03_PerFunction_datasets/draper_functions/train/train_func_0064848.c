find_similar_visual(Screen *screen, Visual *old_visual)
{
  Display *dpy = DisplayOfScreen (screen);
  XVisualInfo vi_in, *vi_out;
  Visual *result = 0;
  int out_count;

  vi_in.screen = screen_number (screen);
  vi_in.class  = visual_class (screen, old_visual);
  vi_in.depth  = visual_depth (screen, old_visual);


  vi_out = XGetVisualInfo (dpy, (VisualScreenMask | VisualClassMask |
				 VisualDepthMask),
			   &vi_in, &out_count);
  if (vi_out && out_count > 0)
    result = vi_out[0].visual;
  if (vi_out) XFree (vi_out);
  vi_out = 0;


  if (!result)
    {
      vi_out = XGetVisualInfo (dpy, (VisualScreenMask | VisualClassMask),
			       &vi_in, &out_count);
      if (vi_out && out_count > 0)
	result = vi_out[0].visual;
      if (vi_out) XFree (vi_out);
      vi_out = 0;
    }


  if (!result)
    result = DefaultVisualOfScreen (screen);

  return result;
}
