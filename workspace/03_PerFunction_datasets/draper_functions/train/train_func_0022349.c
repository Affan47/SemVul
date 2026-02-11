SetStopAngle(RNAngle theta)
{

    stop = theta;
    while (stop >= (start + RN_TWO_PI)) { stop -= RN_TWO_PI; }
    while (stop < start) { stop += RN_TWO_PI; }
    assert((0.0 <= start) && (start <= RN_TWO_PI));
    assert((start <= stop) && (stop <= (start + RN_TWO_PI)));
}
