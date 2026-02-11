time_min(int hour, int minute)
{
    int mm;

    mm = minute / 5;
    if ((minute % 5) > 2)
	mm += 1;
    mm = mm * 5;
    if (mm > 55)
	mm = 0;

    if (mm == 0)
	return "";
    else if (mm == 5)
	return "five past";
    else if (mm == 10)
	return "ten past";
    else if (mm == 15)
	return "quarter past";
    else if (mm == 20)
	return "twenty past";
    else if (mm == 25)
	return "twenty-five past";
    else if (mm == 30)
	return "half past";
    else if (mm == 35)
	return "twenty-five to";
    else if (mm == 40)
	return "twenty to";
    else if (mm == 45)
	return "quarter to";
    else if (mm == 50)
	return "ten to";
    else if (mm == 55)
	return "five to";
    else
	return "five to";
}
