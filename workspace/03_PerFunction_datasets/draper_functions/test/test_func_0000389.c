ompi_group_translate_ranks_strided_reverse (ompi_group_t *child_group,
                                                int n_ranks, const int *ranks1,
                                                ompi_group_t *parent_group,
                                                int *ranks2)
{
    int s,o,i;
    s = child_group->sparse_data.grp_strided.grp_strided_stride;
    o = child_group->sparse_data.grp_strided.grp_strided_offset;
    for (i = 0; i < n_ranks; i++) {
        if ( MPI_PROC_NULL == ranks1[i]) {
            ranks2[i] = MPI_PROC_NULL;
        }
        else {
            ranks2[i] =s*ranks1[i] + o;
        }
    }
    return OMPI_SUCCESS;
}
