bind(int keysym, unsigned int mod)
		{
			int code = XKeysymToKeycode(QX11Info::display(), keysym);


			if (keysym && !code)
				return;

			failed = false;
			XErrorHandler savedErrorHandler = XSetErrorHandler(XGrabErrorHandler);
			WId w = QX11Info::appRootWindow();
			foreach(long mask_mod, X11KeyTriggerManager::ignModifiersList()) {
				XGrabKey(QX11Info::display(), code, mod | mask_mod, w, False, GrabModeAsync, GrabModeAsync);
				GrabbedKey grabbedKey;
				grabbedKey.code = code;
				grabbedKey.mod  = mod | mask_mod;
				grabbedKeys_ << grabbedKey;
			}
			XSync(QX11Info::display(), False);
			XSetErrorHandler(savedErrorHandler);
		}
