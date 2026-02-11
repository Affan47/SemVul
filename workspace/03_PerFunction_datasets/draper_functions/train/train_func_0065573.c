computeActivityEndsStudentsDayPercentages(QWidget* parent)
{
	bool ok=true;

	for(int ai=0; ai<gt.rules.nInternalActivities; ai++)
		activityEndsStudentsDayPercentages[ai]=-1;

	haveActivityEndsStudentsDay=false;

	for(int i=0; i<gt.rules.nInternalTimeConstraints; i++){
		if(gt.rules.internalTimeConstraintsList[i]->type==CONSTRAINT_ACTIVITY_ENDS_STUDENTS_DAY){
			haveActivityEndsStudentsDay=true;

			ConstraintActivityEndsStudentsDay* cae=(ConstraintActivityEndsStudentsDay*)gt.rules.internalTimeConstraintsList[i];

			if(cae->weightPercentage!=100){
				ok=false;

				int t=LongTextMessageBox::mediumConfirmation(parent, GeneratePreTranslate::tr("FET warning"),
				 GeneratePreTranslate::tr("Cannot optimize, because you have constraints of type "
				 "activity activity ends students day for activity with id==%1 with weight percentage under 100%. "
				 "Constraint activity ends students day can only have weight percentage 100%. "
				 "Please modify your data accordingly (remove or edit constraint) and try again.")
				 .arg(gt.rules.internalActivitiesList[cae->activityIndex].id),
				 GeneratePreTranslate::tr("Skip rest"), GeneratePreTranslate::tr("See next"), QString(),
				1, 0 );

				if(t==0)
					break;
			}

			int ai=cae->activityIndex;
			if(activityEndsStudentsDayPercentages[ai] < cae->weightPercentage)
				activityEndsStudentsDayPercentages[ai] = cae->weightPercentage;
		}
		else if(gt.rules.internalTimeConstraintsList[i]->type==CONSTRAINT_ACTIVITIES_END_STUDENTS_DAY){
			haveActivityEndsStudentsDay=true;

			ConstraintActivitiesEndStudentsDay* cae=(ConstraintActivitiesEndStudentsDay*)gt.rules.internalTimeConstraintsList[i];

			if(cae->weightPercentage!=100){
				ok=false;

				int t=LongTextMessageBox::mediumConfirmation(parent, GeneratePreTranslate::tr("FET warning"),
				 GeneratePreTranslate::tr("Cannot optimize, because you have constraints of type "
				 "activity activities end students day with weight percentage under 100%. "
				 "Constraint activities end students day can only have weight percentage 100%. "
				 "Please modify your data accordingly (remove or edit constraint) and try again."),
				 GeneratePreTranslate::tr("Skip rest"), GeneratePreTranslate::tr("See next"), QString(),
				1, 0 );

				if(t==0)
					break;
			}

			for(int i=0; i<cae->nActivities; i++){
				int ai=cae->activitiesIndices[i];
				if(activityEndsStudentsDayPercentages[ai] < cae->weightPercentage)
					activityEndsStudentsDayPercentages[ai] = cae->weightPercentage;
			}
		}
	}

	return ok;
}
