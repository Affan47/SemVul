db_parse(MYSQL_ROW &r) {
    int i=0;
    clear();
    id = atoi(r[i++]);
    create_time = atoi(r[i++]);
    strcpy2(name, r[i++]);
    min_version = atoi(r[i++]);
    deprecated = atoi(r[i++]);
    strcpy2(user_friendly_name, r[i++]);
    homogeneous_redundancy = atoi(r[i++]);
    weight = atof(r[i++]);
    beta = atoi(r[i++]);
    target_nresults = atoi(r[i++]);
    min_avg_pfc = atof(r[i++]);
    host_scale_check = (atoi(r[i++]) != 0);
    homogeneous_app_version = (atoi(r[i++]) != 0);
    non_cpu_intensive = (atoi(r[i++]) != 0);
    locality_scheduling = atoi(r[i++]);
    n_size_classes = atoi(r[i++]);
}
