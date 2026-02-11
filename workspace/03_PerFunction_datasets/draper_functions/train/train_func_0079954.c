db_parse(MYSQL_ROW &r) {
    int i=0;
    clear();
    fileset.id = atoi(r[i++]);
    strcpy2(fileset.name, r[i++]);
    trigger.id = atoi(r[i++]);
    trigger.fileset_id = atoi(r[i++]);
    trigger.need_work = atoi(r[i++]);
    trigger.work_available = atoi(r[i++]);
    trigger.no_work_available = atoi(r[i++]);
    trigger.working_set_removal = atoi(r[i++]);
}
