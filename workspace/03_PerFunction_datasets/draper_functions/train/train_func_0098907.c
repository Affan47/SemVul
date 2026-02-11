getActionTypeString( ActionType type )
{
	QString ret = tr("Unknown");


	switch( type ) {
		case DATE:
			ret = tr("date");
			break;
		case FIRSTTIME:
			ret = tr("first time");
			break;
		case FIRSTTIMELORD:
			ret = tr("first time lord");
			break;
		case NEXTTIME:
			ret = tr("next time");
			break;
		 case CHANGEOWNER:
			ret = tr("change owner");
		default:
			break;
	}

	return ret;
}
