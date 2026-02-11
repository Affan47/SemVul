GetWaitObjects(WaitObjectContainer &container, const CallStack &callStack)
{
	double nextTransceiveTime = TimeToNextTransceive();
	if (nextTransceiveTime)
		container.ScheduleEvent(nextTransceiveTime, CallStack("LimitedBandwidth::GetWaitObjects()", &callStack));
}
