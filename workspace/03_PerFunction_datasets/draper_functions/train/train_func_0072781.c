deleteThread_(Capability *cap, StgTSO *tso)
{


    if (tso->why_blocked == BlockedOnCCall ||
	tso->why_blocked == BlockedOnCCall_Interruptible) {
	tso->what_next = ThreadKilled;
	appendToRunQueue(tso->cap, tso);
    } else {
	deleteThread(cap,tso);
    }
}
