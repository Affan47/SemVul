Scm_MakeGtkRadioGroup(GObject *radio)
{
    GSList *glist = NULL;
    ScmGtkRadioGroup *group;
    if (GTK_IS_RADIO_BUTTON(radio)) {
        glist = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio));
    } else if (GTK_IS_RADIO_MENU_ITEM(radio)) {
        glist = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(radio));
    } else {
        Scm_Error("<gtk-radio-group> can be created only for <gtk-radio-button> or <gtk-radio-menu-item> object, but got an instance of %s",
                  g_type_name(G_OBJECT_TYPE(radio)));
    }
    group = SCM_NEW(ScmGtkRadioGroup);
    SCM_SET_CLASS(group, SCM_CLASS_GTK_RADIO_GROUP);
    if (glist != NULL) {
        group->radio = Scm_MakeGObject(radio);
    } else {
        group->radio = SCM_FALSE;
    }
    return SCM_OBJ(group);
}
