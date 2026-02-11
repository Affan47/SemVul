afr_destroy_pending_matrix (int32_t **pending_matrix, int32_t child_count)
{
        int             i = 0;
        GF_ASSERT (child_count > 0);
        if (pending_matrix) {
                for (i = 0; i < child_count; i++) {
                        if (pending_matrix[i])
                                GF_FREE (pending_matrix[i]);
                }
                GF_FREE (pending_matrix);
        }
}
