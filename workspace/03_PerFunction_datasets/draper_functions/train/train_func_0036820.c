normalize_modifiers (guint keyval,
                     guint modifiers)
{
    switch(keyval) {
    case IBUS_KEY_Control_L:
    case IBUS_KEY_Control_R:
        return modifiers | IBUS_CONTROL_MASK;
    case IBUS_KEY_Shift_L:
    case IBUS_KEY_Shift_R:
        return modifiers | IBUS_SHIFT_MASK;
    case IBUS_KEY_Alt_L:
    case IBUS_KEY_Alt_R:

    case IBUS_KEY_Meta_L:
    case IBUS_KEY_Meta_R:
        return modifiers | IBUS_MOD1_MASK;
    case IBUS_KEY_Super_L:
    case IBUS_KEY_Super_R:
        return modifiers | IBUS_SUPER_MASK;
    case IBUS_KEY_Hyper_L:
    case IBUS_KEY_Hyper_R:
        return modifiers | IBUS_HYPER_MASK;
    default:
        return modifiers;
    }
}
