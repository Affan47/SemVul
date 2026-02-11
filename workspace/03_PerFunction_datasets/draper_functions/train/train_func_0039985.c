grab_startup(gboolean reconfig)
{
    guint i = 0;
    guint num, caps, scroll;

    num = obt_keyboard_modkey_to_modmask(OBT_KEYBOARD_MODKEY_NUMLOCK);
    caps = obt_keyboard_modkey_to_modmask(OBT_KEYBOARD_MODKEY_CAPSLOCK);
    scroll = obt_keyboard_modkey_to_modmask(OBT_KEYBOARD_MODKEY_SCROLLLOCK);

    mask_list[i++] = 0;
    mask_list[i++] = num;
    mask_list[i++] = caps;
    mask_list[i++] = scroll;
    mask_list[i++] = num | caps;
    mask_list[i++] = num | scroll;
    mask_list[i++] = caps | scroll;
    mask_list[i++] = num | caps | scroll;
    g_assert(i == MASK_LIST_SIZE);

    ic = obt_keyboard_context_new(obt_root(ob_screen), grab_window());
}
