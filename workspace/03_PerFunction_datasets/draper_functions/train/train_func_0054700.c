decorate_preedit_string_using_caret_pos(IBusText *text, const IPreeditString& preedit, int caret)
{
    if (caret < preedit.size()) {

        ibus_text_append_attribute(text, IBUS_ATTR_TYPE_UNDERLINE, IBUS_ATTR_UNDERLINE_SINGLE,
                                   caret, preedit.size());
        ibus_text_append_attribute(text, IBUS_ATTR_TYPE_FOREGROUND, WHITE,
                                   caret, preedit.size());
        ibus_text_append_attribute(text, IBUS_ATTR_TYPE_BACKGROUND, GRAY_BLUE,
                                   caret, preedit.size());
    }
}
