saveheaders(std::string &fromhdr, std::string &replytohdr,
			     std::string &customhdr,
			     SaveSink *sink)
{
	AddressList *screenHdrs[]={from, to, cc, bcc, replyto};
	std::vector<mail::emailAddress> *saveBufs[]={&fromV, &toV, &ccV, &bccV,
					   &replytoV};
	std::string headerNames[]={"From", "To", "Cc", "Bcc",
			      "Reply-To"};

	recipients.clear();
	sender="";
	customhdr="";

	size_t i;


	std::string charset= unicode_default_chset();

	for (i=0; i<sizeof(headerNames)/sizeof(headerNames[0]); i++)
	{
		std::vector<mail::emailAddress> addressArray;

		if (screenHdrs[i])
		{
			screenHdrs[i]->getAddresses(addressArray);
		}
		else
			addressArray= *saveBufs[i];

		if (addressArray.size() == 0)
			continue;

		size_t j;

		for (j=0; j<addressArray.size(); j++)
		{
			if (i == 0 && sender.size() == 0)
				sender=addressArray[j].getAddr();

			if (i == 1 || i == 2 || i == 3)
			{
				if (addressArray[j].getAddr().size() > 0)
					recipients.push_back(addressArray[j]
							     .getAddr());
			}
		}

		if (i == 0)
			fromhdr=mail::address::toString("", addressArray);

		if (i == 4)
			replytohdr=mail::address::toString("", addressArray);

		if (sink)
			(*sink) << mail::Header::addresslist(headerNames[i],
							     addressArray)
				.toString()
				<< "\n";
	}


	std::vector<CustomHeader *>::iterator cb, ce;

	cb=customHeaders.begin();
	ce=customHeaders.end();

	while (cb != ce)
	{
		CustomHeader *ch= *cb++;

		std::string v=ch->hiddenValue;

		if (ch->field)
			v=ch->field->getText();

		if (v.size() > 0)
		{
			std::string h=ch->name + " "
				+ (std::string)mail::rfc2047::encode(v, charset);

			if (sink)
				(*sink) << h << "\n";

			if (customhdr.size() > 0)
				customhdr += "\n";
			customhdr += h;
		}
	}

}
