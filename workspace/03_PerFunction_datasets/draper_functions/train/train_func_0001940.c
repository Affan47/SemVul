errorTypeCondToCode(int t, int c)
	{
		Q_UNUSED(t);
		for(int n = 0; errorCodeTable[n].cond; ++n) {
			if(c == errorCodeTable[n].cond)
				return errorCodeTable[n].code;
		}
		return 0;
	}
