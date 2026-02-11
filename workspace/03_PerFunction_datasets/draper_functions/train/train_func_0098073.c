AddEvent(EventProcessor* events, int funcRef, uint32 delay, uint32 calls, Object* obj)
{
    if (!events || funcRef <= 0)
        return 0;
    events->AddEvent(new LuaEvent(E, events, funcRef, delay, calls, obj), events->CalculateTime(delay));
    return funcRef;
}
