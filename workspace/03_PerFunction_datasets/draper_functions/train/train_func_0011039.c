drawInputWires(device& dev)
{
    double dx = (orientation() == kLeftRight) ? dHorz : -dHorz;

    for (unsigned int i=0; i<inputs(); i++) {
        point p = fInputPoint[i];

        dev.fleche(p.x+dx, p.y, 0, orientation());
    }
}
