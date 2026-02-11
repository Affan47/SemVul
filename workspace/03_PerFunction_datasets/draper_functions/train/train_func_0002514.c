Expire_Pilots()
{
    vCFP *pvlist = &vPilots;
    size_t max, ii, xcnt, nxcnt;
    PCF_Pilot pp;
    time_t curr = time(0);
    time_t diff;
    int idiff, iExp;
    iExp = (int)m_PlayerExpires;
    char *tb = GetNxtBuf();
    max = pvlist->size();
    xcnt = 0;
    nxcnt = 0;
    for (ii = 0; ii < max; ii++) {
        pp = &pvlist->at(ii);
        if ( pp->expired ) {
            xcnt++;
        } else {

            diff = curr - pp->last_seen;
            idiff = (int)diff;

            if (idiff > iExp) {
                pp->expired = true;
                pp->exp_time = curr;
                sprintf(tb,"EXPIRED %d",idiff);

                print_pilot(pp, tb, pt_Expired);
                Pilot_Tracker_Disconnect(pp);
                nxcnt++;
            }
        }
    }
    m_ExpiredCnt = (xcnt + nxcnt);

#ifdef ADD_VECTOR_ERASE
    if (m_MaxExpired && (m_ExpiredCnt > m_MaxExpired)) {

        vSZT vst;
        for (ii = 0; ii < max; ii++) {
            pp = &pvlist->at(ii);
            if ( pp->expired ) {
                vst.push_back(ii);
            }
        }
        while (!vst.empty()) {
            ii = vst.back();
            vst.pop_back();
            pvlist->erase(pvlist->begin() + ii);
        }
        ii = pvlist->size();
        SPRTF("%s: Removed %d expired pilots from vector. Was %d, now %d\n", mod_name,
            (int) m_ExpiredCnt, (int) max, (int) ii );
        m_ExpiredCnt = 0;
    }
#endif
}
