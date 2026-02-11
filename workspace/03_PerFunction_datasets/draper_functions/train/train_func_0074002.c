TXT_ButtonKeyPress(TXT_UNCAST_ARG(button), int key)
{
    TXT_CAST_ARG(txt_button_t, button);

    if (key == KEY_ENTER)
    {
        TXT_EmitSignal(button, "pressed");
        return 1;
    }

    return 0;
}
