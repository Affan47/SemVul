Scm_GtkRadioGroupGetGroup(ScmObj g)
{
    GObject *gradio;
    ScmGtkRadioGroup *group;
    if (SCM_FALSEP(g)) return NULL;
    if (!SCM_GTK_RADIO_GROUP_P(g)) {
        Scm_Error("<gtk-radio-group> or #f required, but got %S", g);
    }
    group = SCM_GTK_RADIO_GROUP(g);
    if (SCM_FALSEP(group->radio)) return NULL;
    SCM_ASSERT(SCM_GOBJECT_P(group->radio));
    gradio = SCM_GOBJECT_OBJECT(group->radio);
    if (GTK_IS_RADIO_BUTTON(gradio)) {
        return gtk_radio_button_get_group(GTK_RADIO_BUTTON(gradio));
    }
    if (GTK_IS_RADIO_MENU_ITEM(gradio)) {
        return gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(gradio));
    }
    Scm_Error("internal inconsistency in %S", group);
    return NULL;
}
