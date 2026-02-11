clusterNodeRemoveSlave(clusterNode *master, clusterNode *slave) {
    int j;

    for (j = 0; j < master->numslaves; j++) {
        if (master->slaves[j] == slave) {
            if ((j+1) < master->numslaves) {
                int remaining_slaves = (master->numslaves - j) - 1;
                memmove(master->slaves+j,master->slaves+(j+1),
                        (sizeof(*master->slaves) * remaining_slaves));
            }
            master->numslaves--;
            if (master->numslaves == 0)
                master->flags &= ~REDIS_NODE_MIGRATE_TO;
            return REDIS_OK;
        }
    }
    return REDIS_ERR;
}
