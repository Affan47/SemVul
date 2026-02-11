widget_get_int (const PreferencesWidget * widget)
{
    g_return_val_if_fail (widget->cfg_type == VALUE_INT, 0);

    if (widget->cfg)
        return * (int *) widget->cfg;
    else if (widget->cname)
        return get_int (widget->csect, widget->cname);
    else
        return 0;
}
