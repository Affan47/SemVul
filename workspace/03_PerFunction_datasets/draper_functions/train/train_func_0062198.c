CSigHandler (int sig, siginfo_t *si, void *c)
{
    ucontext_t	    *scp = (ucontext_t *)c;
    vproc_state_t   *vsp = SELF_VPROC;

    vsp->vp_sigCounts[sig].nReceived++;
    vsp->vp_totalSigCount.nReceived++;

#ifdef SIGNAL_DEBUG
SayDebug ("CSigHandler: sig = %d, pending = %d, inHandler = %d\n",
sig, vsp->vp_handlerPending, vsp->vp_inSigHandler);
#endif


    vsp->vp_limitPtrMask = 0;

    if (vsp->vp_inMLFlag && (! vsp->vp_handlerPending) && (! vsp->vp_inSigHandler)) {
	vsp->vp_handlerPending = TRUE;
#ifdef USE_ZERO_LIMIT_PTR_FN
	SIG_SavePC(vsp->vp_state, scp);
	SIG_SetPC(scp, ZeroLimitPtr);
#else
	SIG_ZeroLimitPtr(scp);
#endif
    }

}
