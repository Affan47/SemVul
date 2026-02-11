XtApplyToWidgets (w, proc, arg)
     Widget w;
     XtApplyToWidgetsProc proc;
     XtPointer arg;
{
  if (XtIsComposite (w))
    {
      CompositeWidget cw = (CompositeWidget) w;


      int nkids = cw->composite.num_children;
      Widget *kids = (Widget *) malloc (sizeof (Widget) * nkids);
      int i;
      lwlib_bcopy ((char *) cw->composite.children, (char *) kids,
		   sizeof (Widget) * nkids);
      for (i = 0; i < nkids; i++)


	  {

	    XtApplyToWidgets (kids [i], proc, arg);
	    proc (kids [i], arg);
	  }
      free (kids);
    }
}
