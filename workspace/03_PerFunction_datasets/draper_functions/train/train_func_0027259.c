rsvg_handle_set_dpi_x_y (RsvgHandle * handle, double dpi_x, double dpi_y)
{
    g_return_if_fail (handle != NULL);

    if (dpi_x <= 0.)
        handle->priv->dpi_x = rsvg_internal_dpi_x;
    else
        handle->priv->dpi_x = dpi_x;

    if (dpi_y <= 0.)
        handle->priv->dpi_y = rsvg_internal_dpi_y;
    else
        handle->priv->dpi_y = dpi_y;
}
