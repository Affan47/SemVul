checkVarHooks(const char* name)
{

    static struct
        {
	    const char* name;
	    void (*hook)(void);
	}
    varHooks[] = {
    	#ifdef USE_ICONV
	{ VAR_TO_ENCODING,   encodingHook},
    	{ VAR_FROM_ENCODING, encodingHook},
	#endif
    	{ VAR_LOGGING,       loggingHook},
    	{ VAR_AUTOREPEAT,    arepeatHook},
    	{ VAR_IVIEWER,       iviewerHook},
    	{ VAR_BEMUSED,       bemusedHook},
    	{ VAR_WAITEXEC,      waitTimeoutHook},
    	{ VAR_ALLOWED_ONLY,  allowedOnlyHook},
    	{ NULL,              0}
    };

    size_t idx;
    for (idx = 0; varHooks[idx].name; ++idx) {
    	if (strcmp(name, varHooks[idx].name) == 0) {
    	    if (varHooks[idx].hook != NULL) {
	        (*(varHooks[idx].hook))();
	    }
	    break;
    	}
    }
}
