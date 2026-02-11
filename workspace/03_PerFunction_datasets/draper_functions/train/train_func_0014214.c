element_resource_callback(GtkWidget* widget, gpointer data)
{
  gboolean refresh;
  GList *tmpLst, *eleList;
  VisuElement *ele;
  VisuRenderingSpinResources property;
  gboolean new_bool;
  guint new_int;
  float new_float;
  VisuData *dataObj;

  eleList = visu_ui_panel_elements_getSelected();
  if (!eleList)
    return;

  property = GPOINTER_TO_INT(data);
  refresh = FALSE;
  for (tmpLst = eleList; tmpLst; tmpLst = g_list_next(tmpLst))
    {
      ele = (VisuElement*)tmpLst->data;
      switch (property)
	{
	case VISU_RENDERING_SPIN_HAT_COLOR:
	case VISU_RENDERING_SPIN_TAIL_COLOR:
	case VISU_RENDERING_SPIN_ELIPSOID_COLOR:
	  new_bool = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));

	  DBG_fprintf(stderr, "GtkSpin : Set element '%d' property to %d\n",
		      property, new_bool);
	  refresh = visu_rendering_spin_setResourceBoolean(ele, property, new_bool) || refresh;
	  break;
	case VISU_RENDERING_SPIN_SHAPE:
	  new_int = (guint)gtk_combo_box_get_active(GTK_COMBO_BOX(widget));

	  DBG_fprintf(stderr, "GtkSpin : Set element '%d' property to %d\n",
		      property, new_int);
	  refresh = visu_rendering_spin_setResourceUint(ele, property, new_int) || refresh;
	  if (new_int == VISU_RENDERING_SPIN_ELLIPSOID || new_int == VISU_RENDERING_SPIN_TORUS)
	    {
	      gtk_widget_show(vboxElipsoidShape);
	      gtk_widget_hide(vboxArrowShape);
	    }
	  else
	    {
	      gtk_widget_hide(vboxElipsoidShape);
	      gtk_widget_show(vboxArrowShape);
	    }
	  break;
	case VISU_RENDERING_SPIN_HAT_LENGTH:
	case VISU_RENDERING_SPIN_HAT_RADIUS:
	case spin_VISU_RENDERING_SPIN_TAIL_LENGTH:
	case VISU_RENDERING_SPIN_TAIL_RADIUS:
	case VISU_RENDERING_SPIN_A_AXIS:
	case VISU_RENDERING_SPIN_B_AXIS:
	  new_float = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));

	  DBG_fprintf(stderr, "GtkSpin : Set element '%d' property to %f\n",
		      property, new_float);
	  refresh = visu_rendering_spin_setResourceFloat(ele, property, new_float) || refresh;

	  break;
	default:
	  g_warning("Unknown property '%d' in callback for spin element values.", property);
	  return;
	}
    }

  if(need_redraw && refresh)
    {
      dataObj = visu_ui_panel_getData(VISU_UI_PANEL(VISU_UI_PANEL_ELEMENTS));
      if (!dataObj)
	return;

      for(tmpLst = eleList; tmpLst; tmpLst = g_list_next(tmpLst))
        {
          g_signal_emit_by_name(G_OBJECT(dataObj), "ElementRenderingChanged",
                                (VisuElement*)tmpLst->data, NULL);
          g_signal_emit_by_name(G_OBJECT(dataObj), "RenderingChanged",
                                (VisuElement*)tmpLst->data, NULL);
        }
      VISU_REDRAW_ADD;
    }

  g_list_free(eleList);
}
