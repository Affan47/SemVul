newDay()
{
	TRACE("Engine::newDay");

	_calendar->newDay();
	_server->sendGameCalendar( _players, _calendar);
	checkNewWeek();
}
