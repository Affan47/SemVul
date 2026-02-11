subgroupGetNHoursGaps(int sbg)
{
	if(!mustComputeTimetableSubgroup[sbg])
		return;

	for(int d=0; d<gt.rules.nDaysPerWeek; d++){
		int hours=0, gaps=0, nfirstgaps=0;

		int h;
		for(h=0; h<gt.rules.nHoursPerDay; h++){
			if(newSubgroupsTimetable(sbg,d,h)>=0)
				break;
			else if(!breakDayHour(d,h) && !subgroupNotAvailableDayHour(sbg,d,h))
				nfirstgaps++;
		}
		int ng=0;
		for(; h<gt.rules.nHoursPerDay; h++){
			if(newSubgroupsTimetable(sbg,d,h)>=0){
				hours++;
				gaps+=ng;
				ng=0;
			}
			else if(!breakDayHour(d,h) && !subgroupNotAvailableDayHour(sbg,d,h))
				ng++;
		}
		newSubgroupsDayNGaps(sbg,d)=gaps;
		newSubgroupsDayNHours(sbg,d)=hours;
		if(hours>0)
			newSubgroupsDayNFirstGaps(sbg,d)=nfirstgaps;
		else
			newSubgroupsDayNFirstGaps(sbg,d)=0;
	}


}
