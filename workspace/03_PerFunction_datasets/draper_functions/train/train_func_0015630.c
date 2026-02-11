reg_ontimeout(t_timeout_handler handler, unsigned int numsteps,
           unsigned int stepsize)
{
    ms->ontimeout = handler;
    if (numsteps != 0)
    ms->tm_numsteps = numsteps;
    if (stepsize != 0)
    ms->tm_stepsize = stepsize;
}
