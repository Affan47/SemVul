GetFullDate(byte *mon, byte *day, byte *year)
	{
		static byte const*const Months[]={"",
				"January",
				"February",
				"March",
				"April",
				"May",
				"June",
				"July",
				"August",
				"September",
				"October",
				"November",
				"December"};
		static byte Buf[20];
		sprintf(Buf,"%2.2s",year);

		if((atoi(Buf)>=0) && (atoi(Buf)<70)) sprintf(Buf,"%.2s %s %s%.2s",day,Months[atoi(mon)],"20",year);
			else sprintf(Buf,"%.2s %s %s%.2s",day,Months[atoi(mon)],"19",year);

                        return(Buf);
	}
