afr_mark_child_as_source_by_uid (int32_t *sources, struct iatt *bufs,
                                 int32_t *valid_children, int child_count,
                                 uint32_t uid)
{
        int     i        = 0;
        int     nsources = 0;
        int     child    = 0;

        GF_ASSERT (bufs);
        GF_ASSERT (valid_children);
        GF_ASSERT (sources);
        GF_ASSERT (child_count > 0);

        for (i = 0; i < child_count; i++) {
                if (-1 == valid_children[i])
                        continue;

                child = valid_children[i];
                if (uid == bufs[child].ia_uid) {
                        sources[child] = 1;
                        nsources++;
                }
        }
        return nsources;
}
