getUnprojectedPosition(const Vector2& pos) const
{
    RenderingSurface* rs = &getTargetRenderingSurface();


    if (!rs->isRenderingWindow())
        return pos;


    RenderingWindow* rw = static_cast<RenderingWindow*>(rs);


    Vector2 out_pos(pos);


    while (rw)
    {

        const Vector2 in_pos(out_pos);
        rw->unprojectPoint(in_pos, out_pos);


        rw = (rs = &rw->getOwner())->isRenderingWindow() ?
                static_cast<RenderingWindow*>(rs) : 0;
    }

    return out_pos;
}
