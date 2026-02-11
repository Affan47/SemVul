writeMultipart(std::ostream& ostr)
{
	MultipartWriter writer(ostr, _boundary);
	for (NameValueCollection::ConstIterator it = begin(); it != end(); ++it)
	{
		MessageHeader header;
		std::string disp("form-data; name=\"");
		disp.append(it->first);
		disp.append("\"");
		header.set("Content-Disposition", disp);
		writer.nextPart(header);
		ostr << it->second;
	}
	for (PartVec::iterator ita = _parts.begin(); ita != _parts.end(); ++ita)
	{
		MessageHeader header(ita->pSource->headers());
		std::string disp("form-data; name=\"");
		disp.append(ita->name);
		disp.append("\"");
		std::string filename = ita->pSource->filename();
		if (!filename.empty())
		{
			disp.append("; filename=\"");
			disp.append(filename);
			disp.append("\"");
		}
		header.set("Content-Disposition", disp);
		header.set("Content-Type", ita->pSource->mediaType());
		writer.nextPart(header);
		StreamCopier::copyStream(ita->pSource->stream(), ostr);
	}
	writer.close();
	_boundary = writer.boundary();
}
