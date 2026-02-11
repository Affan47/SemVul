print()
{
	ostringstream s;

	s<<"SweepLineEvent:";
	s<<" xValue="<<xValue<<" deleteEventIndex="<<deleteEventIndex;
	s<<( (eventType==INSERT_EVENT) ? " INSERT_EVENT" : " DELETE_EVENT" );
	s<<endl<<"\tinsertEvent=";
	if (insertEvent) s<<insertEvent->print();
	else s<<"NULL";
	return s.str();
}

}
