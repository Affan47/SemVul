pr_stasche_next(Stasche_table *stasche_table)
{
    int entry = 1;
    int level = 1;

    indent(fp, level);
    fprintf(fp, "mtg_id = %d;\n", stasche_table->mtg_id);
    indent(fp, level);
    fprintf(fp, "mt_num = %d;\n", stasche_table->mt_num);
    for ( ; stasche_table != NULL; stasche_table = stasche_table->succ) {
        indent(fp, level);
        fprintf(fp, "stasche_entry %d {\n", entry);
        pr_stasche_succ(stasche_table);
        indent(fp, level);
        fprintf(fp, "} %%%% stasche_entry %d \n\n", entry);
        entry++;
    }
}
