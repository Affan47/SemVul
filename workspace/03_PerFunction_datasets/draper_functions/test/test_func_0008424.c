abort(std::string errmsg)
{


	mail::addMessage *p=sendMessage;

	sendMessage=NULL;

	if (p)
		p->fail(errmsg);

	p=saveMessage;
	saveMessage=NULL;
	if (p)
		p->fail(errmsg);

	p=postMessage;
	postMessage=NULL;

	if (p)
		p->fail(errmsg);
}
