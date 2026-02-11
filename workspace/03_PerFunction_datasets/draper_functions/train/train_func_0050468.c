init(const char * pidfile, const char * workdir) {
    string tmp;


    char buf[20];
    char cmd[256];
    pid_t pid = getPID(pidfile);
    if (pid > 0) {


	if (snprintf(buf, sizeof(buf), "/proc/%ld", (long int)pid)
		>= (int)sizeof(buf)) {
	    Log(Crit) << "Buffer for string `/proc/" << pid << "' too small"
		      << LogEnd;
	    return 0;
	};
	if (!access(buf, F_OK)) {
	    if(snprintf(buf, sizeof(buf), "/proc/%ld/exe", (long int)pid)
		    >= (int)sizeof(buf)) {
		Log(Crit) << "Buffer for string `/proc/" << pid << "/exe' too small"
			  << LogEnd;
		return 0;
	    }

	    ssize_t len=readlink(buf, cmd, sizeof(cmd));
	    if(len!=-1) {
	        cmd[len]=0;
		if(strstr(cmd, "dibbler")==NULL) {
		    Log(Warning) << "Process is running but it is not Dibbler (pid=" << pid
				 << ", name " << cmd << ")." << LogEnd;
		} else {
    		    Log(Crit) << "Process already running and it seems to be Dibbler (pid="
			      << pid << ", name " << cmd << ")." << LogEnd;
		    return 0;
		}
	    } else {
    		Log(Crit) << "Process already running (pid=" << pid << ", file " << pidfile
		    	  << " is present)." << LogEnd;
		return 0;
	    }
	} else {
	    Log(Warning) << "Pid file found (pid=" << pid << ", file " << pidfile
			 << "), but process " << pid << " does not exist." << LogEnd;
	}
    }

    unlink(pidfile);
    ofstream pidFile(pidfile);
    if (!pidFile.is_open()) {
	Log(Crit) << "Unable to create " << pidfile << " file." << LogEnd;
	return 0;
    }
    pidFile << getpid();
    pidFile.close();
    Log(Notice) << "My pid (" << getpid() << ") is stored in " << pidfile << LogEnd;

    if (chdir(workdir)) {
	Log(Crit) << "Unable to change directory to " << workdir << "." << LogEnd;
	return 0;
    }

    umask(DEFAULT_UMASK);

    return 1;
}
