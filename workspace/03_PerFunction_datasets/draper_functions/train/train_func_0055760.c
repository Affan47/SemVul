cp_time(const String &str, timeval *result)
{
#if TIMESTAMP_PUNS_TIMEVAL
    return cp_time(str, reinterpret_cast<Timestamp*>(result));
#else
    Timestamp t;
    if (cp_time(str, &t)) {
	*result = t.timeval();
	return true;
    } else
	return false;
#endif
}
