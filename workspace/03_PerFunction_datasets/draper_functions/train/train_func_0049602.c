iniblock()
{
    int split, m;
    int i;

    scrbufSize =
        (blockSize / sizeof(word2)) * sizeof(truc);
#ifdef M_LARGE
    auxbufSize =
    (noofblocks*blockSize/2)/sizeof(word2)*sizeof(truc) - scrbufSize;
#else
    auxbufSize = scrbufSize;
    if(noofblocks == 3)
        auxbufSize /= 2;
    else if(noofblocks < 3)
        auxbufSize = 0;
#endif

    m = (noofblocks+1)/2 + 1;
    split = (noofblocks & 1) && (noofblocks < BLOCKMAX);
    if(split) {
        noofblocks++;
        for(i=noofblocks; i>=m; i--)
            Memory[i] = Memory[i-1];
    }
    blockinfo[0].flag = noofblocks;
    for(i=1; i<=noofblocks; i++) {
        blockinfo[i].flag = (i<m ? FREE : RESERVED);
        blockinfo[i].blkbot = 0;
        blockinfo[i].curbot = 0;
        blockinfo[i].blkceil = blockSize;
    }
    if(split) {
        blockinfo[m-1].blkceil = blockSize/2;
        blockinfo[m].blkbot = blockSize/2;
        blockinfo[m].curbot = blockSize/2;
    }
    curblock = 1;
    memBot = blockinfo[curblock].blkbot;
    memCeil = blockinfo[curblock].blkceil;
    AriScratch = (word2 *)Memory[noofblocks];

#ifdef M_LARGE
    auxindex0 = noofblocks/2+1;
#else
    auxindex0 = noofblocks-1;
#endif
    AuxBuf = (word2 *)Memory[auxindex0];
}
