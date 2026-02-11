computeDaytime()
{
	Timespan span(_utcTime/10);
	_hour        = span.hours();
	_minute      = span.minutes();
	_second      = span.seconds();
	_millisecond = span.milliseconds();
	_microsecond = span.microseconds();
}
