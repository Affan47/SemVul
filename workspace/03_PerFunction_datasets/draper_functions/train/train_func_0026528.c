get_autorepeat_state(void) {
#if NO_X11
	RAWFB_RET(0)
	return 0;
#else
	XKeyboardState kstate;

	RAWFB_RET(0)

	X_LOCK;
	XGetKeyboardControl(dpy, &kstate);
	X_UNLOCK;
	return kstate.global_auto_repeat;
#endif
}
