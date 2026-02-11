goo_canvas_widget_class_init (GooCanvasWidgetClass *klass)
{
  GObjectClass *gobject_class = (GObjectClass*) klass;
  GooCanvasItemSimpleClass *simple_class = (GooCanvasItemSimpleClass*) klass;

  gobject_class->dispose = goo_canvas_widget_dispose;

  gobject_class->get_property = goo_canvas_widget_get_property;
  gobject_class->set_property = goo_canvas_widget_set_property;

  simple_class->simple_update        = goo_canvas_widget_update;
  simple_class->simple_paint         = goo_canvas_widget_paint;
  simple_class->simple_is_item_at    = goo_canvas_widget_is_item_at;


  if (!ATK_IS_NO_OP_OBJECT_FACTORY (atk_registry_get_factory (atk_get_default_registry (), GTK_TYPE_WIDGET)))
    {
      atk_registry_set_factory_type (atk_get_default_registry (),
				     GOO_TYPE_CANVAS_WIDGET,
				     goo_canvas_widget_accessible_factory_get_type ());
    }

  g_object_class_install_property (gobject_class, PROP_WIDGET,
				   g_param_spec_object ("widget",
							_("Widget"),
							_("The widget to place in the canvas"),
							GTK_TYPE_WIDGET,
							G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_X,
				   g_param_spec_double ("x",
							"X",
							_("The x coordinate of the widget"),
							-G_MAXDOUBLE,
							G_MAXDOUBLE, 0.0,
							G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_Y,
				   g_param_spec_double ("y",
							"Y",
							_("The y coordinate of the widget"),
							-G_MAXDOUBLE,
							G_MAXDOUBLE, 0.0,
							G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_WIDTH,
				   g_param_spec_double ("width",
							_("Width"),
							_("The width of the widget, or -1 to use its requested width"),
							-G_MAXDOUBLE,
							G_MAXDOUBLE, -1.0,
							G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, PROP_HEIGHT,
				   g_param_spec_double ("height",
							_("Height"),
							_("The height of the widget, or -1 to use its requested height"),
							-G_MAXDOUBLE,
							G_MAXDOUBLE, -1.0,
							G_PARAM_READWRITE));


  g_object_class_install_property (gobject_class, PROP_ANCHOR,
				   g_param_spec_enum ("anchor",
						      _("Anchor"),
						      _("How to position the widget relative to the item's x and y coordinate settings"),
						      GTK_TYPE_ANCHOR_TYPE,
						      GTK_ANCHOR_NW,
						      G_PARAM_READWRITE));

  g_object_class_override_property (gobject_class, PROP_VISIBILITY,
				    "visibility");
}
