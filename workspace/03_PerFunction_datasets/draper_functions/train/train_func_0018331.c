pr_acc_stasche_group(FILE *fp, Hetero_stasche_acc_table* table, int id, int level)
{
    int i;

    if (table == NULL) {
        return;
    }
    indent(fp, level);
    fprintf(fp, "acc_stasche_group %d {\n", id);
    indent(fp, level + 2);
    fprintf(fp, "shared_mtg %d;\n", table->mtg_num);
    indent(fp, level + 2);
    fprintf(fp, "mtg_id ");
    for (i = 0; i < table->mtg_num - 1; i++) {
        fprintf(fp, "%d,", table->mtg_id[i]);
    }
    fprintf(fp, "%d;\n", table->mtg_id[table->mtg_num - 1]);
    indent(fp, level + 2);
    fprintf(fp, "acc_mt {\n");
    pr_hetero_pc_info(fp, table->pc_info, level + 4);
    indent(fp, level + 2);
    fprintf(fp, "}\n");
    indent(fp, level);
    fprintf(fp, "}\n");

}
