setCfCaption(const char * s)
{
    mutexLock(M_STATE);

    if (_state.cf.caption == NULL) {
        _state.cf.caption = stringNew(s);
    } else {
        stringAssign(_state.cf.caption,s);
    }

    mutexUnlock(M_STATE);
}
