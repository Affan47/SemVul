supportsExtension(Extension extension) const
	{
		if(mDebuggerAgent)
			return mDebuggerAgent->supportsExtension(extension);

		return QScriptEngineAgent::supportsExtension(extension);
	}
