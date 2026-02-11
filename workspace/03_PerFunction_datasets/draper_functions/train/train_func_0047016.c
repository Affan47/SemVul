computeLockedUnlockedActivitiesTimeSpace()
{

	idsOfLockedTime.clear();
	idsOfLockedSpace.clear();
	idsOfPermanentlyLockedTime.clear();
	idsOfPermanentlyLockedSpace.clear();

	foreach(TimeConstraint* tc, gt.rules.timeConstraintsList){
		if(tc->type==CONSTRAINT_ACTIVITY_PREFERRED_STARTING_TIME && tc->weightPercentage==100.0 && tc->active){
			ConstraintActivityPreferredStartingTime* c=(ConstraintActivityPreferredStartingTime*) tc;
			if(c->day >= 0  &&  c->hour >= 0) {
				if(c->permanentlyLocked)
					idsOfPermanentlyLockedTime.insert(c->activityId);
				else
					idsOfLockedTime.insert(c->activityId);
			}
		}
	}

	foreach(SpaceConstraint* sc, gt.rules.spaceConstraintsList){
		if(sc->type==CONSTRAINT_ACTIVITY_PREFERRED_ROOM && sc->weightPercentage==100.0 && sc->active){
			ConstraintActivityPreferredRoom* c=(ConstraintActivityPreferredRoom*) sc;

			if(c->permanentlyLocked)
				idsOfPermanentlyLockedSpace.insert(c->activityId);
			else
				idsOfLockedSpace.insert(c->activityId);
		}
	}
}
