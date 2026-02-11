RunWeatherLore(ARegion *r, Unit *u)
{
	ARegion *tar;
	int val, i;

	CastRegionOrder *order = (CastRegionOrder *)u->castorders;

	tar = regions.GetRegion(order->xloc, order->yloc, order->zloc);
	val = GetRegionInRange(r, tar, u, S_WEATHER_LORE);
	if(!val) return 0;

	int level = u->GetSkill(S_WEATHER_LORE);
	int months = 3;
	if(level >= 5) months = 12;
	else if (level >= 3) months = 6;

	AString temp = "Casts Weather Lore on ";
	temp += tar->ShortPrint(&regions);
	temp += ". It will be ";
	int weather, futuremonth;
	for(i = 0; i <= months; i++) {
		futuremonth = (month + i)%12;
		weather=regions.GetWeather(tar, futuremonth);
		temp += SeasonNames[weather];
		temp += " in ";
		temp += MonthNames[futuremonth];
		if(i < (months-1))
			temp += ", ";
		else if(i == (months-1))
			temp += " and ";
		else
			temp += ".";
	}
	u->Event(temp);
	return 1;
}
