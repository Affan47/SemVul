calculation_changed(G_GNUC_UNUSED GtkComboBox *combo, CCViewControls *controls)
{
    controls->args->display_type = gwy_enum_combo_box_get_active(GTK_COMBO_BOX(controls->menu_display));
    controls->args->plane_type = gwy_enum_combo_box_get_active(GTK_COMBO_BOX(controls->menu_plane));
    controls->args->interpolation_type = gwy_enum_combo_box_get_active(GTK_COMBO_BOX(controls->menu_interpolation));

    if (controls->args->crop) {
        gwy_table_hscale_set_sensitive(controls->xplane, FALSE);
        gwy_table_hscale_set_sensitive(controls->yplane, FALSE);
        gwy_table_hscale_set_sensitive(controls->zplane, FALSE);
    }
    else {
       if (controls->args->plane_type == GWY_CC_VIEW_PLANE_X) {
          gwy_table_hscale_set_sensitive(controls->xplane, TRUE);
          gwy_table_hscale_set_sensitive(controls->yplane, FALSE);
          gwy_table_hscale_set_sensitive(controls->zplane, FALSE);
       }
       else if (controls->args->plane_type == GWY_CC_VIEW_PLANE_Y) {
          gwy_table_hscale_set_sensitive(controls->xplane, FALSE);
          gwy_table_hscale_set_sensitive(controls->yplane, TRUE);
          gwy_table_hscale_set_sensitive(controls->zplane, FALSE);
       }
       else if (controls->args->plane_type == GWY_CC_VIEW_PLANE_Z) {
          gwy_table_hscale_set_sensitive(controls->xplane, FALSE);
          gwy_table_hscale_set_sensitive(controls->yplane, FALSE);
          gwy_table_hscale_set_sensitive(controls->zplane, TRUE);
       }
    }
    controls->args->computed = FALSE;
    if (controls->args->update)
                          update_view(controls, controls->args);
}
