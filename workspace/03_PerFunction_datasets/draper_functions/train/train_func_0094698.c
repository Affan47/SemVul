makeUniform(const QRectF &orig, const QRectF &dst)
{
    if (qFuzzyIsNull(orig.x()) || qFuzzyIsNull(orig.y())) {
        return dst;
    }

    QRectF res(dst);
    qreal div_w = dst.width() / orig.width();
    qreal div_h = dst.height() / orig.height();

    qreal div_x = dst.x() / orig.x();
    qreal div_y = dst.y() / orig.y();


    if (!qFuzzyIsNull(div_x) && !qFuzzyCompare(div_w, div_x)) {
        qreal rem_orig = orig.x() - (floor(orig.x()));
        qreal rem_dst = dst.x() - (floor(dst.x()));
        qreal offset = closestDistance(rem_dst, rem_orig);
        res.translate(offset + offset*div_w, 0);
        res.setWidth(res.width() + offset);
    }

    if (!qFuzzyIsNull(div_y) && !qFuzzyCompare(div_h, div_y)) {
        qreal rem_orig = orig.y() - (floor(orig.y()));
        qreal rem_dst = dst.y() - (floor(dst.y()));
        qreal offset = closestDistance(rem_dst, rem_orig);
        res.translate(0, offset + offset*div_h);
        res.setHeight(res.height() + offset);
    }


    return res;
}
