make_menu (GNCSearchCoreType *fe)
{
    GNCSearchAccount *fi = (GNCSearchAccount *)fe;
    GNCSearchAccountPrivate *priv;
    GtkComboBox *combo;
    int initial = 0;

    combo = GTK_COMBO_BOX(gnc_combo_box_new_search());

    priv = _PRIVATE(fi);
    if (priv->match_all)
    {
        gnc_combo_box_search_add(combo, _("matches all accounts"), QOF_GUID_MATCH_ALL);
        initial = QOF_GUID_MATCH_ALL;
    }
    else
    {
        gnc_combo_box_search_add(combo, _("matches any account"), QOF_GUID_MATCH_ANY);
        gnc_combo_box_search_add(combo, _("matches no accounts"), QOF_GUID_MATCH_NONE);
        initial = QOF_GUID_MATCH_ANY;
    }

    gnc_combo_box_search_changed(combo, &fi->how);
    gnc_combo_box_search_set_active(combo, fi->how ? fi->how : initial);

    return GTK_WIDGET(combo);
}
