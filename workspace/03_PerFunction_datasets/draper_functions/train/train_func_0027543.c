fput_tlg_div_num(FILE *fp, Hmdf_tlg_info *hti, int bound)
{
    List *li;

    mfprintf(fp, "===== %B: =====\n", hti->block);
    fprintf(fp,
            "bound_size = %d, pc = %d, pe = %d\n",
            bound,
            hti->hmdf->pc_num,
            hti->hmdf->pe_num);

    for (li = hti->tlg_list; li != NULL; li = li->next) {
        Tlg *tlg = li->data;

        fprintf(fp, "=== TLG%d\n", tlg->no);
        fprintf(fp,
                "total_size = %d, div_num = %d\n",
                tlg->total_data_size,
                tlg->lpdat_head->div_num);
    }
}
