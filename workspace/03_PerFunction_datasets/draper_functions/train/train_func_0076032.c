processSample(const float* vcand, const float cs,
                                              const float* pos, const float rad,
                                              const float vmax, const float* vel, const float* dvel,
                                              dtObstacleAvoidanceDebugData* debug)
{

    float tmin = m_horizTime;
    float side = 0;
    int nside = 0;

    for (int i = 0; i < m_ncircles; ++i)
    {
        const dtObstacleCircle* cir = &m_circles[i];


        float vab[3];
        dtVscale(vab, vcand, 2);
        dtVsub(vab, vab, vel);
        dtVsub(vab, vab, cir->vel);


        side += dtClamp(dtMin(dtVdot2D(cir->dp,vab)*0.5f+0.5f, dtVdot2D(cir->np,vab)*2), 0.0f, 1.0f);
        nside++;

        float htmin = 0, htmax = 0;
        if (!sweepCircleCircle(pos,rad, vab, cir->p,cir->rad, htmin, htmax))
            continue;


        if (htmin < 0.0f && htmax > 0.0f)
        {

            htmin = -htmin * 0.5f;
        }

        if (htmin >= 0.0f)
        {

            if (htmin < tmin)
                tmin = htmin;
        }
    }

    for (int i = 0; i < m_nsegments; ++i)
    {
        const dtObstacleSegment* seg = &m_segments[i];
        float htmin = 0;

        if (seg->touch)
        {

            float sdir[3], snorm[3];
            dtVsub(sdir, seg->q, seg->p);
            snorm[0] = -sdir[2];
            snorm[2] = sdir[0];

            if (dtVdot2D(snorm, vcand) < 0.0f)
                continue;

            htmin = 0.0f;
        }
        else
        {
            if (!isectRaySeg(pos, vcand, seg->p, seg->q, htmin))
                continue;
        }


        htmin *= 2.0f;


        if (htmin < tmin)
            tmin = htmin;
    }


    if (nside)
        side /= nside;

    const float ivmax = 1.0f / vmax;
    const float vpen = m_weightDesVel * (dtVdist2D(vcand, dvel) * ivmax);
    const float vcpen = m_weightCurVel * (dtVdist2D(vcand, vel) * ivmax);
    const float spen = m_weightSide * side;
    const float tpen = m_weightToi * (1.0f/(0.1f+tmin / m_horizTime));

    const float penalty = vpen + vcpen + spen + tpen;


    if (debug)
        debug->addSample(vcand, cs, penalty, vpen, vcpen, spen, tpen);

    return penalty;
}
