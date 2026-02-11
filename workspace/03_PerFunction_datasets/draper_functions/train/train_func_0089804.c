setCfVolume(const char * s)
{
    if (s) {
	    if (_state.cf.volume == NULL) {
            _state.cf.volume =  stringNew(s);
	    } else {
            stringAssign(_state.cf.volume,s);
	    }
    } else {
        setCfVolume("");
    }
}
