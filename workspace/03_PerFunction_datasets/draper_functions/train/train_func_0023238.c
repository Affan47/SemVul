mouseMotion(int x, int y)
	{
		if(mOnMotion.isValid())
			mOnMotion.call(thisObject(), QScriptValueList() << x << y);
	}
