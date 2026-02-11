forkExec(char *cmd)
{
    if(! (strlen(cmd)>0)) return;

    pid_t pid = fork();

    switch (pid) {
        case 0:
            execlp("/bin/sh", "sh", "-c", cmd, NULL);
	    cerr << "exec failed, cleaning up child" << endl;
            exit(1);
        case -1:
	    cerr << "can't fork" << endl;
    }
}
