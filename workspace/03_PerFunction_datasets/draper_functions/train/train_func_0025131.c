runThread(void *arg)
{
    THREAD_STRUCT *s;
    CONDITION cond;
    CTNBOOLEAN abortFlag;
    int runMode;

    s = (THREAD_STRUCT *) arg;

    cond = DUL_AcknowledgeAssociationRQ(&s->association, s->service);
    if (cond != DUL_NORMAL) {
	COND_DumpConditions();
	goto exitLabel;
    }
    if (s->verboseDUL)
	DUL_DumpParams(s->service);
    cond = serviceRequests(s->network, &s->association, s->service,
			s->abortFlag, s->releaseDelay, s->namingConvention);
    if (cond == SRV_PEERREQUESTEDRELEASE)
	cond = SRV_NORMAL;
    if (!s->abortFlag) {
	(void) DUL_DropAssociation(&s->association);
    }
exitLabel:
    abortFlag = s->abortFlag;
    runMode = s->runMode;
    DUL_ClearServiceParameters(s->service);
    free(s->service);
    free(s);
    if (runMode == MODE_FORK) {
	exit(0);
    } else if (runMode == MODE_THREAD) {
#ifdef CTN_USE_THREADS
	THR_ObtainMutex(FAC_ATH);
	completedThreads++;
	THR_ReleaseMutex(FAC_ATH);

#ifdef _MSC_VER
	_endthread();
#else
	pthread_exit(NULL);
#endif
#endif
    } else {
	return 0;
    }
    return 0;
}
