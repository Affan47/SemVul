findWindows(const QRegExp &regExp)
	{
		QList<WindowHandle> back;

		foreach(const WindowHandle &windowHandle, windowList())
		{
			if(regExp.exactMatch(windowHandle.title()))
				back.append(windowHandle);
		}

		return back;
	}
}
