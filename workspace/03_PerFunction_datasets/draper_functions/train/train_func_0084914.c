snmp_collator_sem_wait()
{
    int i = 0;
    int got_sem = 0;

    if (SEM_FAILED == stats_sem) {
        LDAPDebug1Arg(LDAP_DEBUG_ANY,
           "semaphore for stats file (%s) is not available.\n", szStatsFile);
        return;
    }

    for (i=0; i < SNMP_NUM_SEM_WAITS; i++) {
        if (sem_trywait(stats_sem) == 0) {
            got_sem = 1;
            break;
        }
        PR_Sleep(PR_SecondsToInterval(1));
    }

    if (!got_sem) {


        sem_close(stats_sem);
        sem_unlink(stats_sem_name);
        snmp_collator_create_semaphore();
    }
}
