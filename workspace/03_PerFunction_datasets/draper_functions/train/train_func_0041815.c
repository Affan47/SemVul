search_cb(GtkButton * button, gpointer user_data)
{
    GNCGeneralSearch *gsl = user_data;
    GNCGeneralSearchPrivate *priv;
    GNCSearchWindow *sw;

    priv = _PRIVATE(gsl);
    if (priv->sw)
    {
        gnc_search_dialog_raise (priv->sw);
        return;
    }

    sw = (priv->search_cb)(gsl->selected_item, priv->user_data);


    if (sw == NULL)
        return;


    priv->sw = sw;


    gnc_search_dialog_connect_on_close (sw, G_CALLBACK (on_close_cb),
                                        gsl);


    gnc_search_dialog_set_select_cb (sw, new_item_selected_cb,
                                     gsl, gsl->allow_clear);

}
