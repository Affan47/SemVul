fromEvent(QKeyEvent *event)
	{
		mIsQtKey = true;

		for(int i = 0; i < KeyCount; ++i)
		{
			if(event->nativeVirtualKey() == mNativeKey[i])
			{
				mKey = static_cast<Key>(i);
				mIsQtKey = false;
				break;
			}
		}

		switch(event->key())
		{
#ifdef Q_WS_WIN
		case Qt::Key_Shift:
		case Qt::Key_Control:
		case Qt::Key_Alt:
		case Qt::Key_Meta:
		case Qt::Key_AltGr:
			for(int i = 1; i < KeyCount; ++i)
			{
				if(HIBYTE(GetAsyncKeyState(mNativeKey[i])))
				{
					mKey = static_cast<Key>(i);

					mIsQtKey = false;
					break;
				}
			}
			break;
#endif
		default:
			break;
		}

		if(mIsQtKey)
		{
			if(event->modifiers() != Qt::NoModifier)
				return false;

			mKey = event->key();

			if(!KeyMapper::toNativeKey(static_cast<Qt::Key>(mKey)))
				return false;
		}
		else
		{
			if(!nativeKey(mKey))
				return false;
		}

		return true;
	}
