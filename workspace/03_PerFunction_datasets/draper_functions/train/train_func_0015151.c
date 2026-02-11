hmacResponse(int n, string s)
{
	switch (n / 100) {
	case 1:
	case 2:
		authenticated();
		return;
	}

	if ((n / 100) != 3 || s.size() < 4)
	{
		++hmac_method_index;
		authenticate_hmac();
		return;
	}

	s=mail::decodebase64str(s.substr(4));
	s=(*mail::imaphmac::hmac_methods[hmac_method_index])(smtpLoginInfo
							     .pwd, s);

	string sHex;

	{
		ostringstream hexEncode;

		hexEncode << hex;

		string::iterator b=s.begin();
		string::iterator e=s.end();

		while (b != e)
			hexEncode << setw(2) << setfill('0')
				  << (int)(unsigned char)*b++;

		sHex=hexEncode.str();
	}

	s=mail::encodebase64str(smtpLoginInfo.uid + " " + sHex);
	socketWrite(s + "\r\n");
}
