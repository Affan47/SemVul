sysv_kill(std::string pidfile, bool dounlink)
{
	pid_t p = getpid(pidfile);
	if (p > 1) {
		int rc =::kill(p, SIGTERM);
		if (rc == -1) {
			std::cerr << "Error trying to kill pid:" << p << std::endl;
			if (errno == EPERM) {
				std::cerr << "Permission denied." << std::endl;
			}
			return 1;
		}
		if (dounlink) {
			unlink(pidfile.c_str());
			unlink(o.ipc_filename.c_str());
			unlink(o.urlipc_filename.c_str());
		}
		return 0;
	}
	std::cerr << "No DansGuardian process found." << std::endl;
	return 1;
}
