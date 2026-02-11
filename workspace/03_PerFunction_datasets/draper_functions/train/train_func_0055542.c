collectFeedback(collector& c, const point& src, const point& dst, double dx, const point& out)
{
    double	ox = src.x + ((orientation()==kLeftRight) ? dx : -dx);
    double	ct = (orientation()==kLeftRight) ? dWire/2 : -dWire/2;

    point   up(ox, src.y-ct);
    point   br(ox+ct/2.0, src.y);

    c.addOutput(up);
    c.addOutput(br);
    c.addInput(br);

    c.addTrait(trait(up, point(ox, dst.y)));
    c.addTrait(trait(point(ox, dst.y), point(dst.x, dst.y)));
    c.addTrait(trait(src,br));
    c.addTrait(trait(br,out));

}
