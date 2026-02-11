GetDesiredVisual ()
{
  XVisualInfo *v;
  Visual *vis=0;


  v = this->GetDesiredVisualInfo();

  if (v)
    {
    vis = v->visual;
    XFree(v);
    }

  return vis;
}
