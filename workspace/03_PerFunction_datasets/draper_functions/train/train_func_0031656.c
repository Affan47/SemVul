afr_find_child_character_type (int32_t *pending_row, int32_t child,
                               unsigned int child_count)
{
        afr_node_type type = AFR_NODE_INVALID;

        GF_ASSERT ((child >= 0) && (child < child_count));

        if (afr_sh_is_innocent (pending_row, child_count))
                type = AFR_NODE_INNOCENT;
        else if (afr_sh_is_fool (pending_row, child, child_count))
                type = AFR_NODE_FOOL;
        else if (afr_sh_is_wise (pending_row, child, child_count))
                type = AFR_NODE_WISE;
        return type;
}
