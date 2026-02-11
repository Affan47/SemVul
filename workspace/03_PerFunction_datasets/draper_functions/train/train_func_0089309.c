vmCplRecipeTimerStop(PilTime *time)
{

    PilTimer *timer = pilRecGetTimer();


    if (timer == NULL) {
        return 1;
    }

    if (pilTimerIsActive(timer)) {

        PilTime elapsed;
        PilTime start = pilRecGetTimeStart();

        pilTimerStop(timer, NULL);
        elapsed = pilTimerElapsed(timer, NULL);

        pilRecSetTimeStop(start + elapsed);

        if (time != NULL) {
            *time = start + elapsed;
        }

        return 0;
    }

    return 2;

}
