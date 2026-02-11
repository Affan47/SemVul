hime_chewing_cb_register (void)
{
    int nIdx = HIME_CHEWING_KEY_MIN;

    for (; nIdx < HIME_CHEWING_KEY_MAX; nIdx++)
        g_pKeyHandler[nIdx] = (void *)hime_chewing_handler_default;

    g_pKeyHandler[XK_space]     = (void *)chewing_handle_Space;
    g_pKeyHandler[XK_BackSpace] = (void *)hime_chewing_wrapper_bs;
    g_pKeyHandler[XK_Tab]       = (void *)chewing_handle_Tab;
    g_pKeyHandler[XK_Return]    = (void *)hime_chewing_wrapper_enter;
    g_pKeyHandler[XK_Escape]    = (void *)chewing_handle_Esc;
    g_pKeyHandler[XK_Home]      = (void *)hime_chewing_wrapper_home;
    g_pKeyHandler[XK_Left]      = (void *)hime_chewing_wrapper_left;
    g_pKeyHandler[XK_Up]        = (void *)hime_chewing_wrapper_up;
    g_pKeyHandler[XK_Right]     = (void *)hime_chewing_wrapper_right;
    g_pKeyHandler[XK_Down]      = (void *)hime_chewing_wrapper_down;
    g_pKeyHandler[XK_Page_Up]   = (void *)hime_chewing_wrapper_pageup;
    g_pKeyHandler[XK_Page_Down] = (void *)hime_chewing_wrapper_pagedown;
    g_pKeyHandler[XK_End]       = (void *)hime_chewing_wrapper_end;
    g_pKeyHandler[XK_KP_Enter]  = (void *)hime_chewing_wrapper_enter;
    g_pKeyHandler[XK_KP_Left]   = (void *)hime_chewing_wrapper_left;
    g_pKeyHandler[XK_KP_Up]     = (void *)hime_chewing_wrapper_up;
    g_pKeyHandler[XK_KP_Right]  = (void *)hime_chewing_wrapper_right;
    g_pKeyHandler[XK_KP_Down]   = (void *)hime_chewing_wrapper_down;
    g_pKeyHandler[XK_KP_Delete] = (void *)hime_chewing_wrapper_del;
#if 0
    g_pKeyHandler[XK_Shift_L]   = (void *)chewing_handle_ShiftLeft;
    g_pKeyHandler[XK_Shift_R]   = (void *)chewing_handle_ShiftRight;
#endif
    g_pKeyHandler[XK_Delete]    = (void *)hime_chewing_wrapper_del;
}
