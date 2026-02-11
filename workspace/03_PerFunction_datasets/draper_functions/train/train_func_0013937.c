AppendJoinRfmBranch(RfmBlock block, RfmBranch branch)
{
    RfmBranch prev;
    RfmBranch join;

    if ((block == NULL) ||
        (block == NULL)) {
        return;
    }
    prev = NULL;
    for (join = block->join_list;
         join != NULL;
         join = join->join_next) {
        prev = join;
    }
    if (prev) {
        prev->join_next = branch;
        branch->join_prev = prev;
    } else {
        block->join_list = branch;
    }
}
