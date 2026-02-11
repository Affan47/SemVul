level_distance(where)
d_level *where;
{
    register schar ll = depth(&u.uz) - depth(where);
    register boolean indun = (u.uz.dnum == where->dnum);

    if (ll < 0) {
	if (ll < (-8 - rn2(3)))
	    if (!indun)	return "far away";
	    else	return "far below";
	else if (ll < -1)
	    if (!indun)	return "away below you";
	    else	return "below you";
	else
	    if (!indun)	return "in the distance";
	    else	return "just below";
    } else if (ll > 0) {
	if (ll > (8 + rn2(3)))
	    if (!indun)	return "far away";
	    else	return "far above";
	else if (ll > 1)
	    if (!indun)	return "away above you";
	    else	return "above you";
	else
	    if (!indun)	return "in the distance";
	    else	return "just above";
    } else
	    if (!indun)	return "in the distance";
	    else	return "near you";
}
