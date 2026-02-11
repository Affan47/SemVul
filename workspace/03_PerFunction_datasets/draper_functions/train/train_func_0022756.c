CmdAlign(int code)


{
    char *s;
    static char old_alignment_before_center = JUSTIFIED;
    static char old_alignment_before_right = JUSTIFIED;
    static char old_alignment_before_left = JUSTIFIED;
    static char old_alignment_before_centerline = JUSTIFIED;

    if (code == PAR_VCENTER) {
        int restart_field=0;

        if (EQ_field_active()) {
            diagnostics(4,"ending field due to \\vcenter");
            restart_field = 1;
            endCurrentField();
        }

        s = getBraceParam();
        ConvertString(s);
        free(s);

        if (restart_field)
            startField(FIELD_EQ);
        return;
    }

    CmdEndParagraph(0);
    switch (code) {
        case (PAR_CENTERLINE):
            old_alignment_before_centerline = getAlignment();
            setAlignment(CENTERED);
            fprintRTF("{");
            diagnostics(4, "Entering Convert from CmdAlign (centerline)");
            Convert();
            diagnostics(4, "Exiting Convert from CmdAlign (centerline)");
            setAlignment(old_alignment_before_centerline);
            CmdEndParagraph(0);
            fprintRTF("}");
            break;

        case (PAR_RAGGEDRIGHT):
            old_alignment_before_centerline = getAlignment();
            setAlignment(LEFT);

            diagnostics(4, "Entering Convert from CmdAlign (raggedright)");
            Convert();
            diagnostics(4, "Exiting Convert from CmdAlign (raggedright)");
            setAlignment(old_alignment_before_centerline);
            CmdEndParagraph(0);

            break;

        case (PAR_CENTER | ON):
            CmdIndent(INDENT_NONE);
            old_alignment_before_center = getAlignment();
            setAlignment(CENTERED);
            break;
        case (PAR_CENTER | OFF):
            setAlignment(old_alignment_before_center);
            CmdEndParagraph(0);
            CmdIndent(INDENT_INHIBIT);
            break;

        case (PAR_RIGHT | ON):
            old_alignment_before_right = getAlignment();
            setAlignment(RIGHT);
            CmdIndent(INDENT_NONE);
            break;
        case (PAR_RIGHT | OFF):
            setAlignment(old_alignment_before_right);
            CmdIndent(INDENT_INHIBIT);
            break;

        case (PAR_LEFT | ON):
            old_alignment_before_left = getAlignment();
            setAlignment(LEFT);
            CmdIndent(INDENT_NONE);
            break;
        case (PAR_LEFT | OFF):
            setAlignment(old_alignment_before_left);
            CmdIndent(INDENT_INHIBIT);
            break;
        case (PAR_CENTERING):
            CmdIndent(INDENT_NONE);
            old_alignment_before_center = getAlignment();
            setAlignment(CENTERED);
            break;
    }
}
