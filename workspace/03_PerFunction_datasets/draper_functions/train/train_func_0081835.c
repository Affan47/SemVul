inheritedNotEqual(const SVGRenderStyle* other) const
{
    return (fill != other->fill
            || stroke != other->stroke
            || markers != other->markers
            || text != other->text
            || svg_inherited_flags != other->svg_inherited_flags);
}
