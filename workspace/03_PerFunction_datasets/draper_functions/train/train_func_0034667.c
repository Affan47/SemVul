sysv_showpid(std::string pidfile)
{
	pid_t p = getpid(pidfile);
	if (p > 1) {
		std::cout << "Parent DansGuardian pid:" << p << std::endl;
		return 0;
	}
	std::cerr << "No DansGuardian process found." << std::endl;
	return 1;
}
