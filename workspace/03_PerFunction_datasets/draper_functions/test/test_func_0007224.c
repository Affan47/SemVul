set_accepted(const SecureArray &_password)
	{
		QMutexLocker locker(&m);
		accepted = true;
		password = _password;
		done = true;
		if(waiting)
			w.wakeOne();
		else
			QMetaObject::invokeMethod(this, "emitResponseReady", Qt::QueuedConnection);
	}
