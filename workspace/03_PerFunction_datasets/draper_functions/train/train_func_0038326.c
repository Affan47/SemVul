currentColorChanged(const QColor &color)
	{
		if(mOnColorChanged.isValid())
			mOnColorChanged.call(thisObject(), QScriptValueList() << Color::constructor(color, engine()));
	}
