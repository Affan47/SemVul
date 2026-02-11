UpdateVelocityTable() {

        int veldim = -1;
        for (int i = 0 ; i < Dimensions ; i++) {
            if (pDimensionDefinitions[i].dimension == gig::dimension_velocity) {
                veldim = i;
                break;
            }
        }
        if (veldim == -1) return;

        int step = 1;
        for (int i = 0 ; i < veldim ; i++) step <<= pDimensionDefinitions[i].bits;
        int skipveldim = (step << pDimensionDefinitions[veldim].bits) - step;
        int end = step * pDimensionDefinitions[veldim].zones;


        int dim[8] = { 0 };
        for (int i = 0 ; i < DimensionRegions ; i++) {

            if (pDimensionRegions[i]->DimensionUpperLimits[veldim] ||
                pDimensionRegions[i]->VelocityUpperLimit) {

                uint8_t* table = pDimensionRegions[i]->VelocityTable;
                if (!table) {
                    table = new uint8_t[128];
                    pDimensionRegions[i]->VelocityTable = table;
                }
                int tableidx = 0;
                int velocityZone = 0;
                if (pDimensionRegions[i]->DimensionUpperLimits[veldim]) {
                    for (int k = i ; k < end ; k += step) {
                        DimensionRegion *d = pDimensionRegions[k];
                        for (; tableidx <= d->DimensionUpperLimits[veldim] ; tableidx++) table[tableidx] = velocityZone;
                        velocityZone++;
                    }
                } else {
                    for (int k = i ; k < end ; k += step) {
                        DimensionRegion *d = pDimensionRegions[k];
                        for (; tableidx <= d->VelocityUpperLimit ; tableidx++) table[tableidx] = velocityZone;
                        velocityZone++;
                    }
                }
            } else {
                if (pDimensionRegions[i]->VelocityTable) {
                    delete[] pDimensionRegions[i]->VelocityTable;
                    pDimensionRegions[i]->VelocityTable = 0;
                }
            }

            int j;
            int shift = 0;
            for (j = 0 ; j < Dimensions ; j++) {
                if (j == veldim) i += skipveldim;
                else {
                    dim[j]++;
                    if (dim[j] < pDimensionDefinitions[j].zones) break;
                    else {

                        dim[j] = 0;
                        i += ((1 << pDimensionDefinitions[j].bits) -
                              pDimensionDefinitions[j].zones) << shift;
                    }
                }
                shift += pDimensionDefinitions[j].bits;
            }
            if (j == Dimensions) break;
        }
    }
