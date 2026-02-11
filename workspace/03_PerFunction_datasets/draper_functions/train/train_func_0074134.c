doReadMessageContent(const vector<size_t> &messages,
				      bool peek,
				      const mail::mimestruct *msginfo,
				      mail::readMode readType,
				      mail::callback::message &callback)
{
	if (!ready(callback))
		return;

	bool needHeaderDecode=false;
	bool foldHeaders=false;

	string mime_id;
	const mail::mimestruct *parent=msginfo ? msginfo->getParent():NULL;


	if (readType == readBoth)
	{
		if (parent == NULL)
			mime_id="";
		else
			mime_id=parent->mime_id;
	}
	else if (readType == readHeadersFolded ||
		 readType == readHeaders)
	{
		needHeaderDecode=true;

		if (readType == readHeadersFolded)
			foldHeaders=true;

		if (parent == NULL)
			mime_id="HEADER";
		else if (parent->messagerfc822())
			mime_id=parent->mime_id + ".HEADER";
		else
			mime_id=msginfo->mime_id + ".MIME";
	}
	else
	{


		if (parent == NULL)
			mime_id="TEXT";
		else if (parent->messagerfc822())
			mime_id=parent->mime_id + ".TEXT";
		else
			mime_id=msginfo->mime_id;
	}

	string cmd="BODY";

	if (peek)
		cmd="BODY.PEEK";

	mail::imapFolderHeadersCallback *decodeCallback=NULL;

	if (needHeaderDecode)
	{
		if ((decodeCallback=new mail::imapFolderHeadersCallback
		     (foldHeaders, callback)) == NULL)
		{
			callback.fail("Out of memory.");
			return;
		}
	}

	try {
		mail::callback::message *cb= &callback;

		if (decodeCallback)
			cb=decodeCallback;

		messagecmd(messages,
			   " (" + cmd + "[" + mime_id + "])", "UID FETCH",
			   "CONTENTS", *cb);

	} catch (...) {
		if (decodeCallback)
			delete decodeCallback;
		LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
	}
}
