_gnc_dense_cal_set_year(GncDenseCal *dcal, guint year, gboolean redraw)
{
    if (dcal->year == year)
        return;
    dcal->year = year;
    recompute_first_of_month_offset(dcal);
    recompute_extents(dcal);
    if (redraw && gtk_widget_get_realized(GTK_WIDGET(dcal)))
    {
        recompute_x_y_scales(dcal);
        gnc_dense_cal_draw_to_buffer(dcal);
        gtk_widget_queue_draw(GTK_WIDGET(dcal->cal_drawing_area));
    }
}
