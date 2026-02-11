nearestExistingFont (const QFont &font)
{
    QFontDatabase dbase;


    QString family = font.family();
    QString style = dbase.styleString(font);
    qreal size = font.pointSizeF();


    const QStringList families = dbase.families();
    if (!families.contains(family)) {

        family = families.count() ? families[0] : "fixed";

    }


    QString retStyle = dbase.styleString(dbase.font(family, style, 10));
    style = retStyle;


    if (!dbase.isSmoothlyScalable(family, style)) {
        QList<int> sizes = dbase.smoothSizes(family, style);
        if (!sizes.contains(size)) {

            int mindiff = 1000;
            int refsize = size;
            foreach (int lsize, sizes) {
                int diff = qAbs(refsize - lsize);
                if (mindiff > diff) {
                    mindiff = diff;
                    size = lsize;
                }
            }
        }
    }


    QFont result = dbase.font(family, style, int(size));
    if (dbase.isSmoothlyScalable(family, style) && result.pointSize() == floor(size)) {
        result.setPointSizeF(size);
    }
    return result;
}
