Get_Difficulty_Parameters(void *DataPointer)
{
	char *EndOfDataPointer;
	char *startptr;
	char tmp[256];
	const char *diffstr[] = { "easy", "normal", "hard" };
	int i;

#define MAXSPEED_CALIBRATOR_STRING "Droid maxspeed factor in %s: "
#define MAXENERGY_CALIBRATOR_STRING "Droid maximum energy factor in %s: "
#define HEALING_HOSTILE_CALIBRATOR_STRING "Hostile healing speed factor in %s: "
#define HEALING_FRIENDLY_CALIBRATOR_STRING "Friendly healing speed factor in %s: "
#define EXPERIENCE_REWARD_CALIBRATOR_STRING "Droid experience_reward factor in %s: "
#define AGGRESSION_DISTANCE_CALIBRATOR_STRING "Droid aggression distance factor in %s: "

	startptr = LocateStringInData(DataPointer, "*** Start of difficulty parameters ***");
	EndOfDataPointer = LocateStringInData(DataPointer, "*** End of difficulty parameters ***");

	for (i = 0; i < 3; i++) {

		sprintf(tmp, MAXSPEED_CALIBRATOR_STRING, diffstr[i]);
		ReadValueFromString(startptr, tmp, "%lf", &difficulty_parameters[i].maxspeed_calibrator, EndOfDataPointer);

		sprintf(tmp, MAXENERGY_CALIBRATOR_STRING, diffstr[i]);
		ReadValueFromString(startptr, tmp, "%lf", &difficulty_parameters[i].maxenergy_calibrator, EndOfDataPointer);

		sprintf(tmp, HEALING_HOSTILE_CALIBRATOR_STRING, diffstr[i]);
		ReadValueFromString(startptr, tmp, "%f", &difficulty_parameters[i].healing_hostile_calibrator, EndOfDataPointer);

		sprintf(tmp, HEALING_FRIENDLY_CALIBRATOR_STRING, diffstr[i]);
		ReadValueFromString(startptr, tmp, "%f", &difficulty_parameters[i].healing_friendly_calibrator, EndOfDataPointer);

		sprintf(tmp, EXPERIENCE_REWARD_CALIBRATOR_STRING, diffstr[i]);
		ReadValueFromString(startptr, tmp, "%lf", &difficulty_parameters[i].experience_reward_calibrator, EndOfDataPointer);

		sprintf(tmp, AGGRESSION_DISTANCE_CALIBRATOR_STRING, diffstr[i]);
		ReadValueFromString(startptr, tmp, "%lf", &difficulty_parameters[i].aggression_distance_calibrator, EndOfDataPointer);
	}
}
