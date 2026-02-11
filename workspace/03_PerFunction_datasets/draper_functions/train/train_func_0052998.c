hasRelativeValues() const
{
    return (x1().isRelative() || y1().isRelative() ||
            x2().isRelative() || y2().isRelative());
}
