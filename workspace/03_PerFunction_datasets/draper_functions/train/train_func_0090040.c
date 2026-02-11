extractEmails(const String& string) {
	char *emails=string.cstrm();
	String& result=*new String;
	while(char *email=lsplit(&emails, ',')) {
		rsplit(email, '>');
		if(char *in_brackets=lsplit(email, '<'))
			email=in_brackets;
		if(!result.is_empty())
			result<<",";
		extractEmail(result, email);
	}

	return result;
}
