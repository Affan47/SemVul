draw(QPainter* painter, QPainterPath* painterPath, const RenderObject* path, SVGPaintTargetType type) const
{
    if (!setup(painter, painterPath, path, type))
        return;

    renderPath(painter, painterPath, path, type);
    teardown(painter, painterPath, path, type);
}
