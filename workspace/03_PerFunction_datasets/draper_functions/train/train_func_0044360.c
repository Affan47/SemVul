hmdf_pc_and_clustering_number(const Hmdf_table *hmdf_ptr,
                                       int __pe_number,
                                       int *_pc_number, int *clustering_number)
{
    int i, j;

    if (hmdf_ptr == NULL) {
        ERROR_EHMDF;
    }

    *_pc_number = -1;
    *clustering_number = -1;
    for (i = 0; i < hmdf_ptr->clustering_num; i++) {
        for (j = 0; j < hmdf_ptr->pc_num; j++) {
            if ((hmdf_ptr->clustering[i].pcinfo[j].fstpe <= __pe_number)
		&& (hmdf_ptr->clustering[i].pcinfo[j].fstpe +
		    hmdf_ptr->pe_num - 1 >= __pe_number)) {
                *_pc_number = j;
                *clustering_number = i;
                return TRUE;
            }
        }
    }
    return FALSE;
}
