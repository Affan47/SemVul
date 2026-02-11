get_state () const
{
	string msg;
	switch (m_state)
	{
	case xdrIOBuffer::waiting: msg = "waiting"; break;
	case xdrIOBuffer::xmitted: msg = "xmitted"; break;
	case xdrIOBuffer::parsed:  msg = "parsed"; break;
	case xdrIOBuffer::error:   msg = "error"; break;
	}
	return msg;
}
