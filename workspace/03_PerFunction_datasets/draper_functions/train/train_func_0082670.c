BuildRank() {
        size_t num_sblock = n/s;

        Rs = new uint[num_sblock+5];
        for(uint i=0;i<num_sblock+5;i++)
            Rs[i]=0;
        size_t j;
        Rs[0]=0;
        for (j=1;j<=num_sblock;j++) {
            Rs[j]=Rs[j-1];
            Rs[j]+=BuildRankSub((j-1)*factor,factor);
        }
    }
