Scm_GetSignalHandlers(void)
{
    ScmObj h = SCM_NIL, hp;
    ScmObj handlers[SCM_NSIG];
    struct sigdesc *desc;
    sigset_t masterSet;
    int i;


    (void)SCM_INTERNAL_MUTEX_LOCK(sigHandlers.mutex);
    for (i=0; i<SCM_NSIG; i++) handlers[i] = sigHandlers.handlers[i];
    masterSet = sigHandlers.masterSigset;
    (void)SCM_INTERNAL_MUTEX_UNLOCK(sigHandlers.mutex);

    for (desc=sigDesc; desc->name; desc++) {
        if (!sigismember(&masterSet, desc->num)) continue;
        SCM_FOR_EACH(hp, h) {
            if (SCM_EQ(SCM_CDAR(hp), handlers[desc->num])) {
                sigaddset(&(SCM_SYS_SIGSET(SCM_CAAR(hp))->set), desc->num);
                break;
            }
        }
        if (SCM_NULLP(hp)) {
            ScmSysSigset *set = make_sigset();
            sigaddset(&(set->set), desc->num);
            h = Scm_Acons(SCM_OBJ(set), handlers[desc->num], h);
        }
    }
    return h;
}
