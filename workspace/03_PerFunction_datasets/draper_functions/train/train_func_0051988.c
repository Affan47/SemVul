FinishEditing(txt_inputbox_t *inputbox)
{
    if (!inputbox->editing)
    {
        return;
    }


    if (inputbox->widget.widget_class == &txt_inputbox_class)
    {
        free(*((char **)inputbox->value));
        *((char **) inputbox->value) = strdup(inputbox->buffer);
    }
    else if (inputbox->widget.widget_class == &txt_int_inputbox_class)
    {
        *((int *) inputbox->value) = atoi(inputbox->buffer);
    }

    TXT_EmitSignal(&inputbox->widget, "changed");

    inputbox->editing = 0;
}
