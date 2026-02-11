deactivate_unneeded_schedulers(call_scheduler_t *schedulers, char *file)
{
    FILE *f;
    char buffer[1024];
    call_scheduler_t *sched;


    if (!(f = fopen(file,"r"))) return;

    while (fgets(buffer, 1024, f)) {
        for (sched = schedulers; *sched; sched++) {
            if (!strcmp(strtok(buffer, "|"), (*sched)->string)) {
                (*sched)->active = 0;


            }
        }
    }

    fclose(f);

    return;
}
