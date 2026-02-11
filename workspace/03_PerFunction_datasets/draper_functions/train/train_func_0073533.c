apply(const QImage &image, int effect, float value,
                          const QColor &col, bool trans) const
{
    return apply(image, effect, value, col,
                 KColorScheme(QPalette::Active, KColorScheme::View).background().color(), trans);
}
