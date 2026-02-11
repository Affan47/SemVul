operator<<(QDebug dbg, XMPP::NameResolver::Error e)
{
	dbg.nospace() << "XMPP::NameResolver::";

	switch(e)
	{
		case XMPP::NameResolver::ErrorGeneric:
			dbg.nospace() << "ErrorGeneric";
			break;
		case XMPP::NameResolver::ErrorNoName:
			dbg.nospace() << "ErrorNoName";
			break;
		case XMPP::NameResolver::ErrorTimeout:
			dbg.nospace() << "ErrorTimeout";
			break;
		case XMPP::NameResolver::ErrorNoLocal:
			dbg.nospace() << "ErrorNoLocal";
			break;
		case XMPP::NameResolver::ErrorNoLongLived:
			dbg.nospace() << "ErrorNoLongLived";
			break;
	}

	return dbg;
}
