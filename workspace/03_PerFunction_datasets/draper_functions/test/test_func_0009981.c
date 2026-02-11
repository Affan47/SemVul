getContentLength64() const
{
	const std::string& contentLength = get(CONTENT_LENGTH, EMPTY);
	if (!contentLength.empty())
	{
		return NumberParser::parse64(contentLength);
	}
	else return UNKNOWN_CONTENT_LENGTH;
}
