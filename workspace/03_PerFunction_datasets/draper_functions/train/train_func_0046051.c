allocate_colors(GtkWidget * widget)
{

  int lp=sizeof(colors)/sizeof(GdkColor)-1;

  g_debug("allocating colors");


  g_assert(widget->window);
  g_assert(lp<100);
  for(;lp>=0;lp--) {
    features_gc[lp] = gdk_gc_new(widget->window);
    gdk_gc_copy(features_gc[lp], widget->style->white_gc );
    if(gdk_colormap_alloc_color (gdk_colormap_get_system (),
				 & (colors[lp]),
				 FALSE ,
				 TRUE
				 )
       == FALSE)
      g_warning("%s %d : can't allocate color\n",__FILE__,__LINE__);
    else
      gdk_gc_set_foreground ( features_gc[lp], &(colors[lp]));
    g_assert(features_gc[lp]);
  }


  mpl_gc=gdk_gc_new(widget->window);
  g_assert(mpl_gc);
  gdk_gc_copy(mpl_gc, features_gc[1] );
  gdk_gc_set_line_attributes (mpl_gc,
			      1,
			      GDK_LINE_DOUBLE_DASH,
			      GDK_CAP_BUTT,
			      GDK_JOIN_MITER
			      );

  mps_gc=gdk_gc_new(widget->window);
  g_assert(mps_gc);
  gdk_gc_copy(mps_gc, features_gc[2] );
  gdk_gc_set_line_attributes (mps_gc,
			      1,
			      GDK_LINE_DOUBLE_DASH,
			      GDK_CAP_BUTT,
			      GDK_JOIN_MITER
			      );

#ifdef FIXME


  gdk_gc_set_function(mpl_gc,GDK_XOR);
#endif

  flash_gc = gdk_gc_new(widget->window);
  gdk_gc_copy(flash_gc,mpl_gc );
  gdk_gc_set_function(flash_gc,GDK_XOR);


}
