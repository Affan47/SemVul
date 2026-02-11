clusterNodeAddSlave(clusterNode *master, clusterNode *slave) {
    int j;


    for (j = 0; j < master->numslaves; j++)
        if (master->slaves[j] == slave) return REDIS_ERR;
    master->slaves = zrealloc(master->slaves,
        sizeof(clusterNode*)*(master->numslaves+1));
    master->slaves[master->numslaves] = slave;
    master->numslaves++;
    return REDIS_OK;
}
