pr_array_range_semnode(FILE *fp, Array_range_semnode *dim_head)
{
    Array_range_semnode *apt;

    fprintf(fp, "(");
    for (apt = dim_head; apt != NULL; apt = apt->next_dim) {
        fput_semtree_entry(fp, apt->lower_tree);
        fprintf(fp, ":");
        fput_semtree_entry(fp, apt->upper_tree);
        if (apt->next_dim != NULL) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, ")");
}
