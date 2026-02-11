get_attr_name(mail::imap &imapAccount, Token t)
{
	if (t == ')')
	{
		done();
		callback1.success();
		return;
	}

	if (t != ATOM && t != STRING)
	{
		error(imapAccount);
		return;
	}

	attrName=t.text;
	upper(attrName);
	next_func= &mail::imapSTATUS::get_attr_value;
}
