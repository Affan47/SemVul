caldays (year, month)

int	year;
int	month;
{
    if (month < 1) {
	month = month + 12;
	year = year + 1;
	}
    if (month > 12) {
	month = month - 12;
	year = year + 1;
	}
    switch (month) {
	case 1:
	    return (31);
	case 2:
	    if (year%400 == 0)
		return (29);
	    else if (year%100 == 0)
		return (28);
	    else if (year%4 == 0)
		return (29);
	    else
		return (28);
	case 3:
	    return (31);
	case 4:
	    return (30);
	case 5:
	    return (31);
	case 6:
	    return (30);
	case 7:
	    return (31);
	case 8:
	    return (31);
	case 9:
	    return (30);
	case 10:
	    return (31);
	case 11:
	    return (30);
	case 12:
	    return (31);
	default:
	    return (0);
	}
}
