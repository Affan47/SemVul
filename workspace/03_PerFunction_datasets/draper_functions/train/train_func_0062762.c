import_abort_all(ImportJob *job, int wait_for_them)
{
    ImportWorkerInfo *worker;


    job->flags |= FLAG_ABORT;

    for (worker = job->worker_list; worker; worker = worker->next)
        worker->command = ABORT;

    if (wait_for_them) {

        for (worker = job->worker_list; worker != NULL; ) {
            DS_Sleep(PR_MillisecondsToInterval(100));
            if ((worker->state != FINISHED) && (worker->state != ABORTED) &&
                (worker->state != QUIT)) {
                continue;
            } else {
                worker = worker->next;
            }
        }
    }
}
