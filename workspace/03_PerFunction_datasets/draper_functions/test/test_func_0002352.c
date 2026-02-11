get( int num )
{
    switch ( num )
    {
    case dParamLoStop:
        return lostop;
    case dParamHiStop:
        return histop;
    case dParamVel:
        return vel;
    case dParamFMax:
        return fmax;
    case dParamFudgeFactor:
        return fudge_factor;
    case dParamBounce:
        return bounce;
    case dParamCFM:
        return normal_cfm;
    case dParamStopERP:
        return stop_erp;
    case dParamStopCFM:
        return stop_cfm;
    default:
        return 0;
    }
}
