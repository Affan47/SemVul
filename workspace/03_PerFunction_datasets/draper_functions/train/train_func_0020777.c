write_table(void)
{
    FILE *fp;
    rensetu_pair_t *tbl;
    int i;

    fp = cha_fopen(TABLE_FILE, "w", 1);
    fprintf(fp, "%d\n", cell_num);
    for (i = 0, tbl = &rensetu_tbl[0]; i < tbl_num; i++, tbl++) {


	fprintf(fp, "%s %s %s %s\n",
		Cha_hinsi[tbl->hinsi].name ?
		Cha_hinsi[tbl->hinsi].name : "(null)",
		tbl->type ? Cha_type[tbl->type].name : "",
		tbl->form ? Cha_form[tbl->type][tbl->form].name : "",
		tbl->goi ? tbl->goi : "");


	fprintf(fp, "%d %d %d %d %d %s\n",
		tbl->i_pos, tbl->j_pos, tbl->hinsi,
		tbl->type, tbl->form, tbl->goi ? tbl->goi : "*");
    }
    for (; i < cell_num; i++, tbl++)
	fprintf(fp, ";\n%d -1 0 0 0 *\n", tbl->i_pos);

    fclose(fp);
}
