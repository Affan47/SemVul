gwyfile_remove_old_data(GObject *object)
{
    GwyContainer *data;
    GwySelection *rect, *point, *line;

    if (!object || !GWY_IS_CONTAINER(object))
        return;

    data = GWY_CONTAINER(object);


    rect = gwyfile_gather_old_rect_selection(data);
    point = gwyfile_gather_old_point_selection(data);
    line = gwyfile_gather_old_line_selection(data);
    gwy_container_remove_by_prefix(data, "/0/select");
    if (rect) {
        gwy_container_set_object_by_name(data, "/0/select/rectangle", rect);
        g_object_unref(rect);
    }
    if (point) {
        gwy_container_set_object_by_name(data, "/0/select/point", point);
        g_object_unref(point);
    }
    if (line) {
        gwy_container_set_object_by_name(data, "/0/select/line", line);
        g_object_unref(line);
    }


    gwy_container_remove_by_prefix(data, "/0/3d/labels");
    gwy_container_remove_by_name(data, "/0/3d/rot_x");
    gwy_container_remove_by_name(data, "/0/3d/rot_y");
    gwy_container_remove_by_name(data, "/0/3d/view_scale");
    gwy_container_remove_by_name(data, "/0/3d/deformation_z");
    gwy_container_remove_by_name(data, "/0/3d/light_z");
    gwy_container_remove_by_name(data, "/0/3d/light_y");
}
