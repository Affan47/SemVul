curveeditor_widget_get_coordinates(GtkWidget *widget,
        double *x, double *y)
{
    CurveEditorWidgetData *data = g_object_get_data(G_OBJECT(widget),
                                  "curve-widget-data");
    if (data->selectedPoint != -1) {
        *x = data->curve->m_anchors[data->selectedPoint].x;
        *y = data->curve->m_anchors[data->selectedPoint].y;
        return TRUE;
    } else {
        return FALSE;
    }
}
