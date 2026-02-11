vnc_display_keymap_gdk2xtkbd_table(GdkWindow *window,
                                                        size_t *maplen)
{
#ifdef GDK_WINDOWING_X11
	if (GDK_IS_X11_WINDOW(window)) {
		XkbDescPtr desc;
		const gchar *keycodes = NULL;
                GdkDisplay *dpy = gdk_window_get_display(window);


		desc = XkbGetKeyboard(gdk_x11_display_get_xdisplay(dpy),
				      XkbGBN_AllComponentsMask,
				      XkbUseCoreKbd);
		if (desc) {
			if (desc->names) {
				keycodes = gdk_x11_get_xatom_name(desc->names->keycodes);
				if (!keycodes)
					g_warning("could not lookup keycode name");
			}
			XkbFreeKeyboard(desc, XkbGBN_AllComponentsMask, True);
		}

		if (check_for_xwin(dpy)) {
			VNC_DEBUG("Using xwin keycode mapping");
			*maplen = G_N_ELEMENTS(keymap_xorgxwin2xtkbd);
			return keymap_xorgxwin2xtkbd;
		} else if (check_for_xquartz(dpy)) {
			VNC_DEBUG("Using xquartz keycode mapping");
			*maplen = G_N_ELEMENTS(keymap_xorgxquartz2xtkbd);
			return keymap_xorgxquartz2xtkbd;
		} else if (keycodes && STRPREFIX(keycodes, "evdev_")) {
			VNC_DEBUG("Using evdev keycode mapping");
			*maplen = G_N_ELEMENTS(keymap_xorgevdev2xtkbd);
			return keymap_xorgevdev2xtkbd;
		} else if (keycodes && STRPREFIX(keycodes, "xfree86_")) {
			VNC_DEBUG("Using xfree86 keycode mapping");
			*maplen = G_N_ELEMENTS(keymap_xorgkbd2xtkbd);
			return keymap_xorgkbd2xtkbd;
		} else {
			g_warning("Unknown keycode mapping '%s'.\n"
				  "Please report to gtk-vnc-list@gnome.org\n"
				  "including the following information:\n"
				  "\n"
				  "  - Operating system\n"
				  "  - GDK build\n"
				  "  - X11 Server\n"
				  "  - xprop -root\n"
				  "  - xdpyinfo\n",
				  keycodes);
			return NULL;
		}
	}
#endif

#ifdef GDK_WINDOWING_WIN32
	if (GDK_IS_WIN32_WINDOW(window)) {
		VNC_DEBUG("Using Win32 virtual keycode mapping");
		*maplen = G_N_ELEMENTS(keymap_win322xtkbd);
		return keymap_win322xtkbd;
	}
#endif

#ifdef GDK_WINDOWING_QUARTZ
	if (GDK_IS_QUARTZ_WINDOW(window)) {
		VNC_DEBUG("Using OS-X virtual keycode mapping");
		*maplen = G_N_ELEMENTS(keymap_osx2xtkbd);
		return keymap_osx2xtkbd;
	}
#endif

#ifdef GDK_WINDOWING_WAYLAND
	if (GDK_IS_WAYLAND_WINDOW(window)) {
		VNC_DEBUG("Using Wayland Xorg/evdev virtual keycode mapping");
		*maplen = G_N_ELEMENTS(keymap_xorgevdev2xtkbd);
		return keymap_xorgevdev2xtkbd;
        }
#endif

#ifdef GDK_WINDOWING_BROADWAY
	if (GDK_IS_BROADWAY_WINDOW(window)) {
                g_warning("experimental: using broadway, x11 virtual keysym mapping - with very limited support. See also https://bugzilla.gnome.org/show_bug.cgi?id=700105");

			*maplen = G_N_ELEMENTS(keymap_x112xtkbd);
			return keymap_x112xtkbd;
        }
#endif

	g_warning("Unsupported GDK Windowing platform.\n"
		  "Disabling extended keycode tables.\n"
		  "Please report to gtk-vnc-list@gnome.org\n"
		  "including the following information:\n"
		  "\n"
		  "  - Operating system\n"
		  "  - GDK Windowing system build\n");
	return NULL;
}
