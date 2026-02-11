afr_sh_compute_wisdom (int32_t *pending_matrix[],
                       afr_node_character characters[], int child_count)
{
        int i = 0;
        int j = 0;

        for (i = 0; i < child_count; i++) {
                if (characters[i].type == AFR_NODE_WISE) {
                        characters[i].wisdom = 1;

                        for (j = 0; j < child_count; j++) {
                                if ((characters[j].type == AFR_NODE_WISE)
                                    && pending_matrix[j][i]) {

                                        characters[i].wisdom = 0;
                                }
                        }
                }
        }
}
