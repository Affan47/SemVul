assembleMessageRfc822(size_t &handleRet,
					     std::string headers,
					     size_t n,
					     mail::callback &cb)
{
	if (n >= att_list_vec.size())
	{
		errno=EINVAL;
		throw strerror(errno);
	}

	std::vector<mail::Attachment *> a;

	a.push_back(&*att_list_vec[n]);

	assembleContent(handleRet, Attachment(headers, a), cb);
}
