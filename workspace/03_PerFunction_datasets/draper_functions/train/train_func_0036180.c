ibus_text_destroy (IBusText *text)
{
    if (text->text != NULL && text->is_static == FALSE) {
        g_free (text->text);
        text->text = NULL;
    }

    if (text->attrs) {
        g_object_unref (text->attrs);
        text->attrs = NULL;
    }

    IBUS_OBJECT_CLASS (ibus_text_parent_class)->destroy ((IBusObject *)text);
}
