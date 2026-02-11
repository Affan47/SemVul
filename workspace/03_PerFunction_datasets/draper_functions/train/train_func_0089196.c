hexdec(string istring)
{
	double ret = 0;
	istring = trim(istring);
	for(int i = istring.length()-1; i >= 0; --i)
	{
		int num = 0;
		switch(tolower(istring[i]))
		{
			case 'a': num = 10; break;
			case 'b': num = 11; break;
			case 'c': num = 12; break;
			case 'd': num = 13; break;
			case 'e': num = 14; break;
			case 'f': num = 15; break;
			case '1': num = 1; break;
			case '2': num = 2; break;
			case '3': num = 3; break;
			case '4': num = 4; break;
			case '5': num = 5; break;
			case '6': num = 6; break;
			case '7': num = 7; break;
			case '8': num = 8; break;
			case '9': num = 9; break;
			case '0': num = 0; break;
		}
		ret += num*pow((double) 16, (double) istring.length()-i-1);
	}
	return ret;
}
