reset(ResetMode mode)
	{
		if(c)
			c->reset();

		bytesWrittenArgs.clear();
		readyReadTrigger.stop();
		bytesWrittenTrigger.stop();
		finishedTrigger.stop();

		if(mode >= ResetSessionAndData)
		{
			in.clear();
			success = false;
			errorCode = SecureMessage::ErrorUnknown;
			detachedSig.clear();
			hashName = QString();
			signers.clear();
		}

		if(mode >= ResetAll)
		{
			bundleSigner = true;
			format = SecureMessage::Binary;
			to.clear();
			from.clear();
		}
	}
