onElementSelected(VisuUiElementCombobox *combo _U_, GList *elements,
                              gpointer data _U_)
{
  VisuElement *ele;

  DBG_fprintf(stderr, "Panel Elements: set new list of selected elements to %p.\n",
              (gpointer)elements);
  if (elements)
    {
      ele = (VisuElement*)elements->data;
      DBG_fprintf(stderr, "Panel Element: set the selected VisuElement to '%s'.\n",
                  ele->name);
      visu_ui_color_combobox_setRangeColor(VISU_UI_COLOR_COMBOBOX(widgetVisuElementColor), ele->rgb, FALSE);
      visu_ui_color_combobox_setRangeMaterial(VISU_UI_COLOR_COMBOBOX(widgetVisuElementColor),
                                ele->material, FALSE);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkRendered),
				   visu_element_getRendered(ele));
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkMasked),
				   visu_element_getSensitiveToPlanes(ele));
    }

  DBG_fprintf(stderr, "Panel Element: update the render widgets for %p.\n",
              (gpointer)elements);
  if (updateRenderingMethodResources)
    updateRenderingMethodResources(elements);
}
