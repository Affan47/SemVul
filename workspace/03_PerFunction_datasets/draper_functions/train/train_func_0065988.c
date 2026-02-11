set_lpf(PlanesWithSameD &bp, RadiationType radiation, double lambda)
{
    if (lambda == 0)
        bp.lpf = 1.;
    else {
        double T = asin(bp.stol() * lambda);
        if (radiation == kXRay) {


            bp.lpf = (1 + cos(2*T)*cos(2*T)) / (cos(T)*sin(T)*sin(T));
        }
        else if (radiation == kNeutron) {


            bp.lpf = 1 / (4 * sin(T)*sin(T)*cos(T));


        }
    }
}
