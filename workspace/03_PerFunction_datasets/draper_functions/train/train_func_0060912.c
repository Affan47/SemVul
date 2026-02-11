ibus_hotkey_profile_copy (IBusHotkeyProfile       *dest,
                          const IBusHotkeyProfile *src)
{
    gboolean retval;

    retval = parent_class->copy ((IBusSerializable *)dest,
                                 (IBusSerializable *)src);
    g_return_val_if_fail (retval, FALSE);

    g_return_val_if_fail (IBUS_IS_HOTKEY_PROFILE (dest), FALSE);
    g_return_val_if_fail (IBUS_IS_HOTKEY_PROFILE (src), FALSE);

    return TRUE;
}
