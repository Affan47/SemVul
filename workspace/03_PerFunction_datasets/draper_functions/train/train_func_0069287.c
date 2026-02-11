CmdList(int code)


{
    int vspace;
    int amount = 300;

    vspace = getLength("topsep") + getLength("parskip");

    if (code != (INPARAENUM_MODE | ON) && code != (INPARAENUM_MODE | OFF) ) {
        if (getTexMode() == MODE_VERTICAL)
            vspace += getLength("partopsep");
        else
            CmdEndParagraph(0);
    }

    switch (code) {
        case (ITEMIZE_MODE | ON):
            setVspace(vspace);
            PushEnvironment(ITEMIZE_MODE);
            setLength("parindent", -amount);
            setLeftMarginIndent(getLeftMarginIndent() + 2 * amount);
            CmdIndent(INDENT_USUAL);
            break;

        case (ENUMERATE_MODE | ON):
            setVspace(vspace);
            PushEnvironment(ENUMERATE_MODE);
            g_enumerate_depth++;
            CmdItem(RESET_ITEM_COUNTER);
            setLength("parindent", -amount);
            setLeftMarginIndent(getLeftMarginIndent() + 2 * amount);
            CmdIndent(INDENT_USUAL);
            break;

        case (DESCRIPTION_MODE | ON):
            setVspace(vspace);
            PushEnvironment(DESCRIPTION_MODE);
            setLength("parindent", -amount);
            setLeftMarginIndent(getLeftMarginIndent() + 2 * amount);
            CmdIndent(INDENT_USUAL);
            break;

        case (INPARAENUM_MODE | ON):
            PushEnvironment(INPARAENUM_MODE);
            g_enumerate_depth++;
            CmdItem(RESET_ITEM_COUNTER);
            break;

        case (INPARAENUM_MODE | OFF):
            g_enumerate_depth--;
            PopEnvironment();
            g_processing_list_environment = FALSE;
            break;

        case (ENUMERATE_MODE | OFF):
            g_enumerate_depth--;
        case (ITEMIZE_MODE | OFF):
        case (DESCRIPTION_MODE | OFF):
            PopEnvironment();
            CmdIndent(INDENT_INHIBIT);
            g_processing_list_environment = FALSE;
            setVspace(vspace);
            break;
    }
}
