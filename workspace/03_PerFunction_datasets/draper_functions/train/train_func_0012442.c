run_restart_tests(struct crut_pipes *pipes, int count, int stopped)
{
    int child = pipes->child;


    restart(pipes, NULL);
    count += stopped ? check_stopped(pipes, child, count)
		     : check_running(pipes, child, count);


    restart(pipes, "--cont");
    count += check_running(pipes, child, count);


    restart(pipes, "--stop");
    count += check_stopped(pipes, child, count);

    return 7 + !!stopped;
}
