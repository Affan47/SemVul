mkbitmask(branchRec  **bidx,
                     int        bnum,
                     Bit_vector       ***bmp)
{
    int     byte1, bmsk, mcnt, i, mtn, mtn0;
    Bit_vector    **bitmask;

    mcnt=mtn0=0;
    for (i=0 ; i<bnum ; i++) {
        mtn=bidx[i]->mtn;
        if (mtn!=mtn0) {
            mcnt++;
            mtn0=mtn;
        }
    }
    bitmask=(mcnt!=0)?malloc(mcnt*sizeof(Bit_vector*)):NULL;
    for (i=0 ; i<mcnt ; i++)
        bitmask[i]=calloc((bnum+7)/8,sizeof(Bit_vector));
    mtn0=0;
    mcnt=-1;
    for (i=0 ; i<bnum ; i++) {
        if ((mtn=bidx[i]->mtn)!=mtn0) {
            mcnt++;
            mtn0=mtn;
        }
        byte1=i>>3;
        bmsk=1<<(i&7);
        bitmask[mcnt][byte1]|=bmsk;
    }
    *bmp=bitmask;

    return  mcnt+1;
}
