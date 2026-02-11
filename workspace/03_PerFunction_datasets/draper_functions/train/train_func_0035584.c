imc_get_skip_coeff(IMCContext* q) {
    int i, j;

    memset(q->skipFlagBits, 0, sizeof(q->skipFlagBits));
    memset(q->skipFlagCount, 0, sizeof(q->skipFlagCount));
    for(i = 0; i < BANDS; i++) {
        if (!q->bandFlagsBuf[i] || !q->bandWidthT[i])
            continue;

        if (!q->skipFlagRaw[i]) {
            q->skipFlagBits[i] = band_tab[i+1] - band_tab[i];

            for(j = band_tab[i]; j < band_tab[i+1]; j++) {
                if ((q->skipFlags[j] = get_bits1(&q->gb)))
                    q->skipFlagCount[i]++;
            }
        } else {
            for(j = band_tab[i]; j < (band_tab[i+1]-1); j += 2) {
                if(!get_bits1(&q->gb)){
                    q->skipFlagBits[i]++;
                    q->skipFlags[j]=1;
                    q->skipFlags[j+1]=1;
                    q->skipFlagCount[i] += 2;
                }else{
                    if(get_bits1(&q->gb)){
                        q->skipFlagBits[i] +=2;
                        q->skipFlags[j]=0;
                        q->skipFlags[j+1]=1;
                        q->skipFlagCount[i]++;
                    }else{
                        q->skipFlagBits[i] +=3;
                        q->skipFlags[j+1]=0;
                        if(!get_bits1(&q->gb)){
                            q->skipFlags[j]=1;
                            q->skipFlagCount[i]++;
                        }else{
                            q->skipFlags[j]=0;
                        }
                    }
                }
            }

            if (j < band_tab[i+1]) {
                q->skipFlagBits[i]++;
                if ((q->skipFlags[j] = get_bits1(&q->gb)))
                    q->skipFlagCount[i]++;
            }
        }
    }
}
