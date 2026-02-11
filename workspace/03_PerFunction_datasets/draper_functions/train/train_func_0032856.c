equals(const QScriptValue &other) const
	{
		if(other.isUndefined() || other.isNull())
			return false;

		QObject *object = other.toQObject();
		if(Rect *otherRect = qobject_cast<Rect*>(object))
			return (otherRect == this || otherRect->mRect == mRect);

		return false;
	}
