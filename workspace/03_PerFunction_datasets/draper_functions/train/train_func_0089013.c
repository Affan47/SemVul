classname() const
	{
#ifdef Q_WS_X11
		XClassHint *hint = XAllocClassHint();
		QString back;

		if(XGetClassHint(QX11Info::display(), mValue, hint))
			back = QString::fromLatin1(hint->res_class);

		XFree(hint);

		return back;
#endif
#ifdef Q_WS_WIN
		wchar_t className[255];

		GetClassName(mValue, className, sizeof(className)-1);

		return QString::fromWCharArray(className);
#endif
	}
