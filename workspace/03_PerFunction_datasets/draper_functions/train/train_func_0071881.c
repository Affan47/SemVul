mapMouseEvent(int x_, int y_, int width_, int height_,
                                   RenderObject::NodeInfo& info)
{
    bool inside = false;
    if (width_ != lastw || height_ != lasth)
    {
        region=getRegion(width_, height_);
        lastw=width_; lasth=height_;
    }
    if (region.contains(QPoint(x_,y_)))
    {
        inside = true;
        info.setInnerNode(this);
        info.setURLElement(this);
    }

    return inside;
}
