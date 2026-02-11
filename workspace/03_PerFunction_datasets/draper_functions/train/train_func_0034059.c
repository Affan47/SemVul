numlock_set_xkb_state (GsdNumLockState new_state)
{
        unsigned int num_mask;
        Display *dpy = GDK_DISPLAY_XDISPLAY (gdk_display_get_default ());
        if (new_state != GSD_NUM_LOCK_STATE_ON && new_state != GSD_NUM_LOCK_STATE_OFF)
                return;
        num_mask = numlock_NumLock_modifier_mask ();
        XkbLockModifiers (dpy, XkbUseCoreKbd, num_mask, new_state == GSD_NUM_LOCK_STATE_ON ? num_mask : 0);
}
