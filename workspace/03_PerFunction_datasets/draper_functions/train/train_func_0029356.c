project_update(int id, POptions po)
{
    PProject pp;

    pit_db_load();
    id = project_find_current(id, &pp);

    if (po->project.name)   strncpy(pp->name,   po->project.name,   sizeof(pp->name)   - 1);
    if (po->project.status) strncpy(pp->status, po->project.status, sizeof(pp->status) - 1);
    strncpy(pp->username, current_user(), sizeof(pp->username) - 1);
    pit_table_mark(projects, pp->id);

    project_log_update(pp, po);
    pit_db_save();
}
