DetectLoop(const gHitData& hit, gLoopData loopData[2])
    {

        gCycle *other = hit.otherCycle;

        if (other)
        {

            {
                REAL    dist  = hit.driveDistance;
                int otherSide = hit.lr < 0 ? 0 : 1;
                for (int i=1; i>=0; i--)
                {
                    loopData[i].closedIn.SetLen(0);
                    loopData[i].loop = false;

                    int lr   = i+i-1;
                    int dir  = hit.lr * lr > 0 ? 1 : 0;
                    int winding = 0;
                    bool loop = CheckLoop(cycle, other,
                                          dist, otherSide, dir,
                                          loopData[i].closedIn, winding);

                    if (loop)
                    {


                        winding += cycle->WindingNumber();

                        winding -= hit.windingNumber;


                        winding += lr;

#ifdef DEBUG_X
                        if (winding != 4 && winding != -4)
                        {
                            gRandomController noRandom;
                            if (winding != 0)


                                winding = 0;
                            CheckLoop(cycle, other,
                                      dist, otherSide, dir,
                                      loopData[i].closedIn, winding);

                            winding += cycle->WindingNumber();
                            winding -= hit.windingNumber;
                            winding += lr;
                        }
#endif

#ifdef DEBUG

#endif


                        if (winding * lr > 0)
                            loopData[i].loop = true;

                        loopData[i].winding = winding;
                    }
                }
            }
        }
    }
