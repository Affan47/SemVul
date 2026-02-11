text_render_h_adjustment_changed (GtkAdjustment *adjustment, gpointer data)
{
    g_return_if_fail (adjustment != NULL);
    g_return_if_fail (data != NULL);

    TextRender *obj = TEXT_RENDER (data);

    if ((obj->priv->old_h_adj_value != adjustment->value) ||
        (obj->priv->old_h_adj_lower != adjustment->lower) ||
        (obj->priv->old_h_adj_upper != adjustment->upper))
    {
        text_render_h_adjustment_update (obj);

        obj->priv->old_h_adj_value = adjustment->value;
        obj->priv->old_h_adj_lower = adjustment->lower;
        obj->priv->old_h_adj_upper = adjustment->upper;
    }
}
