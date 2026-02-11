child_handler(int sig)
{
    pico_child_done = 1;
    if(pico_child_jmp_ok){
#ifdef	sco


	signal(SIGALRM, SIG_IGN);
	alarm(0);
#endif
	longjmp(pico_child_state, 1);
    }
}
