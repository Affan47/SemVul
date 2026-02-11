open (const string& cmd_, const string& type_)
{
	trace_with_mask("Pipe::open", PIPE);

#if !defined(WIN32)

	if (type_ != "r" && type_ != "w") {
		EL((ASSAERR,"Wrong type \"%s\"\n", type_.c_str ()));
		errno = EINVAL;
		return NULL;
	}

	int fd [2];
	if (pipe (fd) < 0) {
		EL((ASSAERR,"failed: pipe(2)\n"));
		return NULL;
	}
	Fork f (Fork::KILL_ON_EXIT, Fork::IGNORE_STATUS);

	if (f.isChild ()) {
		if (type_ == "r") {
			::close (fd [0]);
			if (fd [1] != STDOUT_FILENO) {
				dup2 (fd [1], STDOUT_FILENO);
				::close (fd [1]);
			}
		}
		else {
			::close (fd [1]);
			if (fd [0] != STDIN_FILENO) {
				dup2 (fd [0], STDIN_FILENO);
				::close (fd [0]);
			}
		}

		DL((PIPE,"Executing cmd: \"%s\"\n", cmd_.c_str ()));
		execl ("/bin/sh", "sh", "-c", cmd_.c_str (), (char* ) 0);
		EL((ASSAERR,"failed: execl(2)\n"));
		_exit (127);
	}

	if (type_ == "r") {
		::close (fd [1]);
		if ((m_fp = fdopen (fd [0], type_.c_str ())) == NULL) {
			EL((ASSAERR,"failed: fdopen ()\n"));
			return NULL;
		}
	}
	else {
		::close (fd [0]);
		if ((m_fp = fdopen (fd [1], type_.c_str ())) == NULL) {
			EL((ASSAERR,"failed: fdopen ()\n"));
			return NULL;
		}
	}
	m_child_pid = f.getChildPID ();
	DL((PIPE,"m_child_pid = %d\n",m_child_pid));
	return m_fp;

#else
     DL((ASSAERR|PIPE,"Not implemented for win32!\n"));
     return NULL;
#endif
}
