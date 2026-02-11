openGlkWindows() {
    glkMainWin = glk_window_open(0, 0, 0, wintype_TextBuffer, 0);
    if (glkMainWin == NULL) {
            printf("FATAL ERROR: Cannot open initial window");
            glk_exit();
    }
#ifdef HAVE_GARGLK
   glk_stylehint_set (wintype_TextGrid, style_User1, stylehint_ReverseColor, 1);
#endif
    glkStatusWin = glk_window_open(glkMainWin, winmethod_Above |
                                   winmethod_Fixed, 1, wintype_TextGrid, 0);
    glk_set_window(glkStatusWin);
    glk_set_style(style_Preformatted);
    glk_set_window(glkMainWin);
}
