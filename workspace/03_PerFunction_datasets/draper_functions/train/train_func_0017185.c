EpochTimeToString(long long time)
{
	static int textIndex=0;
	static char text[4][64];

	if (++textIndex==4)
		textIndex=0;

	struct tm * timeinfo;
	time_t t = time;
	timeinfo = localtime ( &t );
	strftime (text[textIndex],64,"%c.",timeinfo);


	return text[textIndex];
}
