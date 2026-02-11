icaldurationtype_from_string(const char* str)
{

    int i;
    int begin_flag = 0;
    int time_flag = 0;
    int date_flag = 0;
    int week_flag = 0;
    int digits=-1;
    int scan_size = -1;
    int size = strlen(str);
    char p;
    struct icaldurationtype d;

    memset(&d, 0, sizeof(struct icaldurationtype));

    for(i=0;i != size;i++){
	p = str[i];

	switch(p)
	    {
	    case '-': {
		if(i != 0 || begin_flag == 1) goto error;

		d.is_neg = 1;
		break;
	    }

	    case 'P': {
		if (i != 0 && i !=1 ) goto error;
		begin_flag = 1;
		break;
	    }

	    case 'T': {
		time_flag = 1;
		break;
	    }

	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		{


		    if(digits != -1){
			break;
		    }

		    if (begin_flag == 0) goto error;

		    scan_size = sscanf((char*)(str+i),"%d",&digits);
		    if(scan_size == 0) goto error;
		    break;
		}

	    case 'H': {
		if (time_flag == 0||week_flag == 1||d.hours !=0||digits ==-1)
		    goto error;
		d.hours = digits; digits = -1;
		break;
	    }
	    case 'M': {
		if (time_flag == 0||week_flag==1||d.minutes != 0||digits ==-1)
		    goto error;
		d.minutes = digits; digits = -1;
		break;
	    }
	    case 'S': {
		if (time_flag == 0||week_flag==1||d.seconds!=0||digits ==-1)
		    goto error;
		d.seconds = digits; digits = -1;
		break;
	    }
	    case 'W': {
		if (time_flag==1||date_flag==1||d.weeks!=0||digits ==-1)
		    goto error;
		week_flag = 1;
		d.weeks = digits; digits = -1;
		break;
	    }
	    case 'D': {
		if (time_flag==1||week_flag==1||d.days!=0||digits ==-1)
		    goto error;
		date_flag = 1;
		d.days = digits; digits = -1;
		break;
	    }
	    default: {
		goto error;
	    }

	    }
    }

    return d;


 error:
    icalerror_set_errno(ICAL_MALFORMEDDATA_ERROR);
    memset(&d, 0, sizeof(struct icaldurationtype));
    return d;

}
