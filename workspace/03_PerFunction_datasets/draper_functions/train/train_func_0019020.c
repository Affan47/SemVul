getDelayTarget (HsInt us)
{
    Time elapsed;
    elapsed = getProcessElapsedTime();


    if (us > TimeToUS(TIME_MAX - elapsed)) {
        return TimeToLowResTimeRoundDown(TIME_MAX);
    } else {


        return TimeToLowResTimeRoundUp(elapsed + USToTime(us));
    }
}
