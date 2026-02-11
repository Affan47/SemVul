doobj()
{
	char	i;


	if (fixed[object] == loc || here(object))
		trobj();


	else if (object == GRATE) {
		if (loc == 1 || loc == 4 || loc == 7) {
			motion = DEPRESSION;
			domove();
		}
		else if (loc>9 && loc<15) {
			motion = ENTRANCE;
			domove();
		}
	}


	else if (dcheck() && dflag >= 2) {
		object = DWARF;
		trobj();
	}


	else if ((liq() == object && here(BOTTLE)) ||
		 liqloc(loc) == object)
		trobj();
	else if (object == PLANT && at(PLANT2) &&
		prop[PLANT2] == 0) {
		object = PLANT2;
		trobj();
	}


	else if (object == KNIFE && knfloc == loc) {
		rspeak(116);
		knfloc = -1;
	}


	else if (object == ROD && here(ROD2)) {
		object = ROD2;
		trobj();
	}
	else
		printf("I see no %s here.\n", probj(object));
}
