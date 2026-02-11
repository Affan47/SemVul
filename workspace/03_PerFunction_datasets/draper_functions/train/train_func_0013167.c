verifyTimers(void* key, void* value, void* user_data)
{


    if (timerAllowed != RC_OK) return;

    int ticksInSec = CAST_POINTER_TO_INT(user_data);

    timerCmd *tm = (timerCmd *) value;
    if (!value) return;

    if (tm->status == ID_TIMER_CONTINUE) {


	if (tm->ticks >= (tm->timeout * ticksInSec)) {
    	    DEBUG2("verifyTimers(): it is time to execute %s", tm->macro);

    	    macroCmdCallback(tm->macro, NULL, NULL);

    	    tm->ticks = 0;

    	    if (tm->max_times > 0) {
    		tm->times++;
    		if (tm->times >= tm->max_times) {
    		    DEBUG2("verifyTimers(): timer %s self-canceled", tm->macro);


		    tm->status = ID_TIMER_CANCEL;
    		}
    	    }
    	} else {
    	    tm->ticks++;
    	}
    } else if (tm->status == ID_TIMER_CANCEL) {
    	deleteTimer(tm->macro);
    }
}
