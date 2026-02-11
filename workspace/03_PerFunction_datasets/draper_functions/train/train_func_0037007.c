SetRealTime()
{
    if (fDriver->IsRealTime()) {
        jack_log("JackThreadedDriver::Init real-time");

        GetEngineControl()->fPeriod = GetEngineControl()->fConstraint = GetEngineControl()->fPeriodUsecs * 1000;
        GetEngineControl()->fComputation = JackTools::ComputationMicroSec(GetEngineControl()->fBufferSize) * 1000;
        fThread.SetParams(GetEngineControl()->fPeriod, GetEngineControl()->fComputation, GetEngineControl()->fConstraint);
        if (fThread.AcquireSelfRealTime(GetEngineControl()->fServerPriority) < 0) {
            jack_error("AcquireSelfRealTime error");
        } else {
            set_threaded_log_function();
        }
    } else {
        jack_log("JackThreadedDriver::Init non-realtime");
    }
}
