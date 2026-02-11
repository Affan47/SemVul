exceptionThrow(qint64 scriptId, const QScriptValue &exception, bool hasHandler)
	{
		if(mDebuggerAgent)
			mDebuggerAgent->exceptionThrow(scriptId, exception, hasHandler);
	}
