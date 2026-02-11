ConcreteStart(void) throw(Err)
	{
		if (mOut) fclose(mOut);
		if (mIn) fclose(mIn);

		mIn = 0;
		mOut = 0;

		if (mInputs.size() && mOutputs.size() && mDevice!="-")
		{
			throw Err("TextFileMIDIDevice: Cannot use the same file for reading and writing");
		}
		if (mInputs.size())
		{
			if (mDevice == "-")
				mIn = stdin;
			else
				mIn = fopen(mDevice.c_str(),"r");
		}
		if (mOutputs.size())
		{
			if (mDevice == "-")
				mOut = stdout;
			else
				mOut = fopen(mDevice.c_str(),"w");
		}
	}
