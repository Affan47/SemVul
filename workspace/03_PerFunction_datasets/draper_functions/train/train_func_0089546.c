validate(size_t rowNum,
				 string addresses)
{
	size_t errIndex;

	vector<mail::emailAddress> addrvecNative;

	{
		vector<mail::address> addrvec;

		if (!mail::address::fromString(addresses, addrvec, errIndex))
		{
			statusBar->clearstatus();
			statusBar->status(strerror(errno));
			statusBar->beepError();
			return false;
		}

		if (errIndex <= addresses.size())
		{


			string s=addresses.substr(0, errIndex);

			widecharbuf wc;

			wc.init_string(s);

			fields[rowNum]->requestFocus();
			fields[rowNum]->setCursorPos(wc.wcwidth(0));
			statusBar->clearstatus();
			statusBar->status(_("Syntax error"));
			statusBar->beepError();
			return false;
		}


		addrvecNative.reserve(addrvec.size());

		vector<mail::address>::iterator b, e;

		for (b=addrvec.begin(), e=addrvec.end(); b != e; ++b)
		{
			mail::emailAddress newAddress;

			std::string errmsg=newAddress
				.setDisplayName(b->getName(),
						unicode_default_chset());

			if (errmsg == "")
				errmsg=newAddress
					.setDisplayAddr(b->getAddr(),
							unicode_default_chset()
							);

			if (errmsg != "")
			{
				statusBar->clearstatus();
				statusBar->status(errmsg);
				statusBar->beepError();
				return false;
			}

			addrvecNative.push_back(newAddress);
		}
	}

	return validate(rowNum, addrvecNative);
}
