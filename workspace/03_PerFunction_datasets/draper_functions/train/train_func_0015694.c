getClosestIndices(const int* vertsa, const int nvertsa,
                              const int* vertsb, const int nvertsb,
                              int& ia, int& ib)
{
    int closestDist = 0xfffffff;
    ia = -1, ib = -1;
    for (int i = 0; i < nvertsa; ++i)
    {
        const int in = (i+1) % nvertsa;
        const int ip = (i+nvertsa-1) % nvertsa;
        const int* va = &vertsa[i*4];
        const int* van = &vertsa[in*4];
        const int* vap = &vertsa[ip*4];

        for (int j = 0; j < nvertsb; ++j)
        {
            const int* vb = &vertsb[j*4];

            if (ileft(vap,va,vb) && ileft(va,van,vb))
            {
                const int dx = vb[0] - va[0];
                const int dz = vb[2] - va[2];
                const int d = dx*dx + dz*dz;
                if (d < closestDist)
                {
                    ia = i;
                    ib = j;
                    closestDist = d;
                }
            }
        }
    }
}
