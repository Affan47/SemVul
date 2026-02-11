fill_datetime(char* datestr, char* timestr)
{
	    struct icaltimetype stm;

	    memset(&stm,0,sizeof(stm));

	    if (datestr != 0){
		sscanf(datestr,"%4d%2d%2d",&(stm.year), &(stm.month),
		       &(stm.day));
	    }

	    if (timestr != 0){
		sscanf(timestr,"%2d%2d%2d", &(stm.hour), &(stm.minute),
		       &(stm.second));
	    }

	    return stm;

}
