allocateVT(struct display *d)
{
    struct display *cd;
    int i, tvt, volun;

    if ((d->displayType & d_location) == dLocal &&
        d->status == notRunning && !d->serverVT && d->reqSrvVT >= 0)
    {
        if (d->reqSrvVT && d->reqSrvVT < 16) {
            d->serverVT = d->reqSrvVT;
        } else {
            for (i = tvt = 0;;) {
                if (serverVTs[i]) {
                    tvt = atoi(serverVTs[i++]);
                    volun = False;
                    if (tvt < 0) {
                        tvt = -tvt;
                        volun = True;
                    }
                    if (!tvt || tvt >= 16)
                        continue;
                } else {
                    if (++tvt >= 16)
                        break;
                    volun = True;
                }
                for (cd = displays; cd; cd = cd->next) {
                    if (cd->reqSrvVT == tvt &&
                            (cd->status != zombie || cd->zstatus != DS_REMOVE))
                        goto next;
                    if (cd->serverVT == tvt) {
                        if (cd->status != zombie || cd->zstatus == DS_REMOTE)
                            goto next;
                        if (!cd->follower) {
                            d->serverVT = -1;
                            cd->follower = d;
                            return;
                        }
                    }
                }
                if (!volun || !((1 << tvt) & getBusyVTs())) {
                    d->serverVT = tvt;
                    return;
                }
          next: ;
            }
        }
    }
}
