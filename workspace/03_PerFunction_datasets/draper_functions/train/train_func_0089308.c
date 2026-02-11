scroll_box_get_v_adjustment (ScrollBox *obj)
{
    g_return_val_if_fail (obj != NULL, NULL);
    g_return_val_if_fail (IS_SCROLL_BOX(obj), NULL);

    return gtk_range_get_adjustment (GTK_RANGE(obj->priv->vscroll));
}
