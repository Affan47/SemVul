afr_local_child_exists (afr_child_pos_t *pos, unsigned int child_count)
{
        int             i = 0;
        gf_boolean_t    local = _gf_false;

        for (i = 0; i < child_count; i++, pos++) {
                if (*pos == AFR_POS_LOCAL) {
                        local = _gf_true;
                        break;
                }
        }
        return local;
}
