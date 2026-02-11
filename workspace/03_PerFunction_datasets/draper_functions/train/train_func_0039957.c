task_log_create(PTask pt)
{
    Action a = { pt->project_id, pt->id, 0 };

    sprintf(a.message, "created task %d: %s (status: %s, priority: %s", pt->id, pt->name, pt->status, pt->priority);
    if (pt->date > 0) sprintf(a.message + strlen(a.message), ", date: %s", format_date(pt->date));
    if (pt->time > 0) sprintf(a.message + strlen(a.message), ", time: %s", format_time(pt->time));
    sprintf(a.message + strlen(a.message), ", project: %d)", pt->project_id);
    pit_action(&a);
}
