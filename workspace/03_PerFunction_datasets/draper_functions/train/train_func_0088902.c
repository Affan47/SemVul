free_classified_ready_tasks(ready_tasks *src,
                           int max_tlg)
{
    int i;

    for (i = 0; i < max_tlg + 1; i++) {
        free(src->dlg_task[i]);
        free(src->belong_dlg_task[i]);
    }
    free(src->dlg_task);
    free(src->dlg_tasks);
    free(src->belong_dlg_task);
    free(src->belong_dlg_tasks);
    free(src->not_dlg_task);
    free(src->car_task);
    free(src);
}
