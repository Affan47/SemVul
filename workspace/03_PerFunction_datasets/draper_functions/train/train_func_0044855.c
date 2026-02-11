pit_db_save() {
    char *file_name = pit_file_name();
    FILE *file = fopen(file_name, "wb");

    if (!file) {
        perish(file_name);
    } else {
        write_header(file);
        pit_table_save(file, projects);
        pit_table_save(file, tasks);
        pit_table_save(file, notes);
        pit_table_save(file, actions);
        fclose(file);
    }
}
