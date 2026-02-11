gwy_tool_read_value_update_values(GwyToolReadValue *tool)
{
    GwyPlainTool *plain_tool;
    gboolean is_selected = FALSE;
    gdouble point[2];
    gdouble xoff, yoff;
    gint col, row;

    plain_tool = GWY_PLAIN_TOOL(tool);
    if (plain_tool->data_field && plain_tool->selection)
        is_selected = gwy_selection_get_object(plain_tool->selection, 0, point);

    if (!is_selected) {
        gtk_label_set_text(GTK_LABEL(tool->x), NULL);
        gtk_label_set_text(GTK_LABEL(tool->xpx), NULL);
        gtk_label_set_text(GTK_LABEL(tool->y), NULL);
        gtk_label_set_text(GTK_LABEL(tool->ypx), NULL);
        gtk_label_set_text(GTK_LABEL(tool->z), NULL);
        gtk_label_set_text(GTK_LABEL(tool->theta), NULL);
        gtk_label_set_text(GTK_LABEL(tool->phi), NULL);
        return;
    }

    xoff = gwy_data_field_get_xoffset(plain_tool->data_field);
    yoff = gwy_data_field_get_yoffset(plain_tool->data_field);

    col = floor(gwy_data_field_rtoj(plain_tool->data_field, point[0]));
    row = floor(gwy_data_field_rtoi(plain_tool->data_field, point[1]));

    update_label(plain_tool->coord_format, tool->x, point[0] + xoff);
    update_label(tool->pixel_format, tool->xpx, col);
    update_label(plain_tool->coord_format, tool->y, point[1] + yoff);
    update_label(tool->pixel_format, tool->ypx, row);
    gwy_tool_read_value_calculate(tool, col, row);

    if (tool->has_calibration)
          update_label_unc(plain_tool->value_format,
                           tool->z,
                           tool->avg,
                           gwy_data_field_get_dval_real(tool->zunc,
                                                        point[0],
                                                        point[1],
                                                        GWY_INTERPOLATION_BILINEAR));
    else update_label(plain_tool->value_format, tool->z, tool->avg);

    if (tool->same_units) {
        update_label(tool->angle_format, tool->theta,
                     180.0/G_PI*atan(hypot(tool->bx, tool->by)));
        update_label(tool->angle_format, tool->phi,
                     180.0/G_PI*atan2(tool->by, tool->bx));
    }
    else {
        gtk_label_set_text(GTK_LABEL(tool->theta), _("N.A."));
        gtk_label_set_text(GTK_LABEL(tool->phi), _("N.A."));
    }
}
