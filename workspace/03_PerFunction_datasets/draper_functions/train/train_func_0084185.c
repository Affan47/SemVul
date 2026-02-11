egetenv(const char *s)
{
#if defined(HAVE_GETENV)
	char *rval = (char *)"";
#endif
	if (!strcmp(s, "PWD")) {
		return (char *) pwd();
	} else if (!strcmp(s, "USER")) {
#if defined(HAVE_GETENV)
		rval = (char *)getenv(s);
		if (rval == NULL)
			return (char *)"";
		else
			return rval;
#else
		return (char *)"unknown";
#endif
	} else if (!strcmp(s, "SYSTEM")) {
#if defined(VMS)
		return (char *)"vax";
#elif defined(MSDOS)
		return (char *)"msdos";
#else
		return (char *)"unix";
#endif
	} else if (!strcmp(s, "HOST")) {
#if defined(HAVE_GETENV)
		rval = (char *)getenv(s);
		if (rval == NULL)
			return (char *)"";
		else
			return rval;
#else
		return (char *)"unknown";
#endif
	} else if (!strcmp(s, "HOME")) {
#if defined(HAVE_GETENV)
		rval = (char *)getenv(s);
		if (rval == NULL)
			return (char *)"";
		else
			return rval;
#else
		return (char *)"unknown";
#endif
	} else if (!strcmp(s, "PAGER")) {
#if defined(HAVE_GETENV)
		rval = (char *)getenv(s);
		if (rval == NULL)
			return (char *)"";
		else
			return rval;
#else
		return (char *)"unknown";
#endif
	} else if (!strcmp(s, "GRIINPUTS")) {
#if defined(HAVE_GETENV)
		rval = (char *)getenv(s);
		if (rval == NULL)
			return (char *)"";
		else
			return rval;
#else
		return "";
#endif
	} else {
#if defined(HAVE_GETENV)
		rval = (char *)getenv(s);
		if (rval == NULL)
			return (char*)"";
		else
			return rval;
#else
		return "unknown";
#endif
	}
}
