genericMessageRead(string uid,
				    size_t messageNumber,
				    bool peek,
				    mail::readMode getType,
				    callback::message &callback)
{
	if (openedGroup.size() == 0)
	{
		callback.fail("Invalid message number.");
		return;
	}

	if (fixGenericMessageNumber(uid, messageNumber) &&
	    genericCachedUid(uid))
	{


		vector<size_t> vec;

		vec.push_back(messageNumber);
		readMessageContent(vec, peek, getType, callback);
		return;
	}

	installTask(new FetchTask(&callback, *this, openedGroup,
				  messageNumber, uid, getType));
}
