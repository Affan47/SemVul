ConcreteConfigure(const ProcessingConfig& c)
	throw(ErrProcessingObj)
{
	bool ret = MIDIOut::ConcreteConfigure(c);

	if (ret==false) return false;

	MIDI::Message m = MIDI::Message(mConfig.GetMessage());

	mMessageSize = MIDI::GetMessageInfo(m).length;


	mControlledBytes = MIDI::GetMessageInfo(m).length;

	if (mConfig.GetChannel()!=0) mControlledBytes--;


	if (mConfig.GetFirstData()!=128) mControlledBytes--;

	mControlsReceived = 0;


	if (mMessage) delete [] mMessage;
	mMessage = new unsigned char[mMessageSize];

	if (mReceivedUniqId) delete [] mReceivedUniqId;
	mReceivedUniqId = new unsigned char[mControlledBytes];

	if (mControlIdToMsgByteId) delete mControlIdToMsgByteId;
	mControlIdToMsgByteId = new unsigned char[mControlledBytes];


	for (int i = 0; i < mControlledBytes ; i++ )
	{
		mReceivedUniqId[i] = mUniqId;
	}

	if (m==MIDI::eNoteOnOff) m = MIDI::eNoteOn;

	mStatusByte = 0x80|(int(m)<<4);

	int ctrlid = 0;


	for (int i=0;i<MIDI::GetMessageInfo(m).length;i++)
	{
		const char* fieldname = 0;


		switch (i)
		{
			case 0:
				if (mConfig.GetChannel()==0)

					fieldname = "Channel";
				else


					mStatusByte |= (mConfig.GetChannel()+1);
				break;
			case 1:
				if (mConfig.GetFirstData()==128)

					fieldname = MIDI::GetMessageInfo(m).field[i-1];
				else

					mMessage[1] = mConfig.GetFirstData();
				break;
			default:

				fieldname = MIDI::GetMessageInfo(m).field[i-1];
				break;
		}
		if (fieldname)
		{
			std::string controlName = std::string(MIDI::GetMessageInfo(m).name) + ":" + fieldname;


			mControlIdToMsgByteId[ctrlid] = i;
			mMyInControls.AddElem(new FloatInControl(ctrlid++,controlName,this,&MIDIOutControl::DoControl));
		}
	}

	return true;
}
