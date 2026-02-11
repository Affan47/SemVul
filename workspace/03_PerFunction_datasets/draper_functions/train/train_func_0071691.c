computeFixedActivities(QWidget* parent)
{
	bool ok=true;

	for(int ai=0; ai<gt.rules.nInternalActivities; ai++){
		int notAllowedSlots=0;
		for(int tim=0; tim<gt.rules.nHoursPerWeek; tim++)
			if(notAllowedTimesPercentages[ai][tim]==100)
				notAllowedSlots++;

		if(notAllowedSlots==gt.rules.nHoursPerWeek){
			ok=false;

			QString s=GeneratePreTranslate::tr("Activity with id=%1 has no allowed slot - please correct that").arg(gt.rules.internalActivitiesList[ai].id);
			int t=LongTextMessageBox::mediumConfirmation(parent, GeneratePreTranslate::tr("FET warning"), s,
			 GeneratePreTranslate::tr("Skip rest"), GeneratePreTranslate::tr("See next"), QString(),
			 1, 0 );

			if(t==0)
				return false;
		}
		else if(notAllowedSlots==gt.rules.nHoursPerWeek-1)
			fixedTimeActivity[ai]=true;
		else
			fixedTimeActivity[ai]=false;


		fixedSpaceActivity[ai]=false;
		foreach(PreferredRoomsItem it, activitiesPreferredRoomsList[ai])
			if(it.percentage==100.0 && it.preferredRooms.count()==1){
				fixedSpaceActivity[ai]=true;
				break;
			}
	}

	return ok;
}
