prepgc()
{
    int i, first = 1;
    for(i=1; i<=noofblocks; i++) {
        blockinfo[i].curbot = blockinfo[i].blkbot;
        if(blockinfo[i].flag == RESERVED) {
            blockinfo[i].flag = FREE;
            if(first) {
                curblock = i;
                memBot = blockinfo[i].curbot;
                memCeil = blockinfo[i].blkceil;
                first = 0;
            }
        }
        else
            blockinfo[i].flag = RESERVED;
    }
}
