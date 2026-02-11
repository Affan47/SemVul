internal_readFromStream(mrpt::utils::CStream &in)
{
	in.ReadBuffer(&header,sizeof(header));
	uint32_t nBytesInStream;
	in >> nBytesInStream;
	msg_body.resize(nBytesInStream);
	if (nBytesInStream)
		in.ReadBuffer(&msg_body[0],sizeof(nBytesInStream));
}
