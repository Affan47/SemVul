TXT_WindowActionDrawer(TXT_UNCAST_ARG(action))
{
    TXT_CAST_ARG(txt_window_action_t, action);
    char buf[10];

    TXT_GetKeyDescription(action->key, buf);

    if (TXT_HoveringOverWidget(action))
    {
        TXT_BGColor(TXT_COLOR_BLACK, 0);
    }

    TXT_DrawString(" ");
    TXT_FGColor(TXT_COLOR_BRIGHT_GREEN);
    TXT_DrawString(buf);
    TXT_FGColor(TXT_COLOR_BRIGHT_CYAN);
    TXT_DrawString("=");

    TXT_FGColor(TXT_COLOR_BRIGHT_WHITE);
    TXT_DrawString(action->label);
    TXT_DrawString(" ");
}
