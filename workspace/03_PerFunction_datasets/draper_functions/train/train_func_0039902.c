text_render_v_adjustment_value_changed (GtkAdjustment *adjustment, gpointer data)
{
    g_return_if_fail (adjustment != NULL);
    g_return_if_fail (data != NULL);

    TextRender *obj = TEXT_RENDER (data);

    if (obj->priv->old_v_adj_value != adjustment->value)
    {
        text_render_v_adjustment_update (obj);
        obj->priv->old_v_adj_value = adjustment->value;
    }
}
