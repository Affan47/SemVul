rtcSetDataTime(int year, int month, int day, int hour, int minute, int second) {

	if ((RTC->ISR & RTC_ISR_INITF) == (uint32_t)RESET) {
		RTC_WriteProtectionCmd(DISABLE);


		RTC->ISR = (uint32_t)RTC_INIT_MASK;


		return 0;
	}

	else {
		RTC_TimeTypeDef time;
		RTC_DateTypeDef date;
		uint32_t tmpreg;

		date.RTC_Year = year - 2000;
		date.RTC_Month = month;
		date.RTC_Date = day;
		date.RTC_WeekDay = rtcDow(2000+date.RTC_Year, date.RTC_Month, date.RTC_Date);


		tmpreg = (((uint32_t)rtcByteToBcd2(date.RTC_Year) << 16) | \
				  ((uint32_t)rtcByteToBcd2(date.RTC_Month) << 8) | \
				  ((uint32_t)rtcByteToBcd2(date.RTC_Date)) | \
				  ((uint32_t)date.RTC_WeekDay << 13));

		RTC->DR = (uint32_t)(tmpreg & RTC_DR_RESERVED_MASK);

		time.RTC_Hours = hour;
		time.RTC_Minutes = minute;
		time.RTC_Seconds = second;
		time.RTC_H12 = 0x00;


		tmpreg = (uint32_t)(((uint32_t)rtcByteToBcd2(time.RTC_Hours) << 16) | \
							((uint32_t)rtcByteToBcd2(time.RTC_Minutes) << 8) | \
							((uint32_t)rtcByteToBcd2(time.RTC_Seconds)) | \
							(((uint32_t)time.RTC_H12) << 16));

		RTC->TR = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);


		RTC_ExitInitMode();
		RTC_WriteProtectionCmd(ENABLE);

		AQ_PRINTF("RTC set: %d-%02d-%02d %02d:%02d:%02d UTC\n", date.RTC_Year+2000, date.RTC_Month, date.RTC_Date, time.RTC_Hours, time.RTC_Minutes,
				  time.RTC_Seconds);


		return 1;
	}
}
