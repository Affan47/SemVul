hasInactiveActivities(Rules& r)
{


	int cnt=0;
	foreach(int aid, this->activitiesIds)
		if(r.inactiveActivities.contains(aid))
			cnt++;

	if(this->activitiesIds.count()>=2 && (cnt==this->activitiesIds.count() || cnt==this->activitiesIds.count()-1) )
		return true;
	else
		return false;
}
