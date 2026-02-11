TXT_ButtonDrawer(TXT_UNCAST_ARG(button))
{
    TXT_CAST_ARG(txt_button_t, button);
    int i;
    int w;

    w = button->widget.w;

    TXT_SetWidgetBG(button);

    TXT_DrawString(button->label);

    for (i=strlen(button->label); i < w; ++i)
    {
        TXT_DrawString(" ");
    }
}
