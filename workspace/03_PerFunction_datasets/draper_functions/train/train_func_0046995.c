ConnectRfmBranch(RfmBranch branch,
                 RfmBlock  fork_block,
                 RfmBlock  join_block)
{
    RfmBranch del;
    RfmBranch fork;

    if ((branch == NULL) ||
        (fork_block == NULL) ||
        (join_block == NULL)) {
        return;
    }
    switch (branch->branch_kind) {
    case RFM_BRANCH_UNCONDITIONAL:
        while (fork_block->fork_list) {
            del = fork_block->fork_list;
            DisconnectRfmBranch(del);
            DeleteRfmBranch(del);
        }
        break;
    case RFM_BRANCH_TAKEN:
        fork = fork_block->fork_list;
        while (fork) {
            if (fork->branch_kind == RFM_BRANCH_NOT_TAKEN) {
                fork = fork->fork_next;
                continue;
            }
            del = fork;
            fork = fork->fork_next;
            DisconnectRfmBranch(del);
            DeleteRfmBranch(del);
        }
        break;
    case RFM_BRANCH_NOT_TAKEN:
        fork = fork_block->fork_list;
        while (fork) {
            if (fork->branch_kind == RFM_BRANCH_TAKEN) {
                fork = fork->fork_next;
                continue;
            }
            del = fork;
            fork = fork->fork_next;
            DisconnectRfmBranch(del);
            DeleteRfmBranch(del);
        }
        break;
    case RFM_BRANCH_SWITCH:
        fork = fork_block->fork_list;
        while (fork) {
            if (fork->branch_kind == RFM_BRANCH_SWITCH) {
                fork = fork->fork_next;
                continue;
            }
            del = fork;
            fork = fork->fork_next;
            DisconnectRfmBranch(del);
            DeleteRfmBranch(del);
        }
        break;
    default:
        return;
    }
    branch->fork_block = fork_block;
    AppendForkRfmBranch(fork_block, branch);
    branch->join_block = join_block;
    AppendJoinRfmBranch(join_block, branch);
}
