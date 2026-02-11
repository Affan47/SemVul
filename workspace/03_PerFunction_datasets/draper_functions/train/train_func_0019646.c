fillenvelope(mail::imapparsefmt &imapenvelope,
			 mail::envelope &envelope)
{
	if (imapenvelope.children.size() < 10)
		return false;

	vector<mail::imapparsefmt *>::iterator b=imapenvelope.children.begin();


	envelope.date=rfc822_parsedt((*b)->value.c_str()); b++;

	envelope.subject= (*b)->value; b++;

	parse_addr_list(*b, envelope.from); b++;
	parse_addr_list(*b, envelope.sender); b++;
	parse_addr_list(*b, envelope.replyto); b++;
	parse_addr_list(*b, envelope.to); b++;
	parse_addr_list(*b, envelope.cc); b++;
	parse_addr_list(*b, envelope.bcc); b++;

	envelope.inreplyto= (*b)->value; b++;
	envelope.messageid= (*b)->value;
	return true;
}
