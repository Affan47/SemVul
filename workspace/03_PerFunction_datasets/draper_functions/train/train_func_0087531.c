spawn_filemanager (const char *dir)
{


	int pid = fork ();
	if (pid == 0) {
		execlp (config_filemanager, config_filemanager, dir, NULL);
		exit (0);
	}
}
