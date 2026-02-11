inheritFrom(const SVGRenderStyle* svgInheritParent)
{
    if (!svgInheritParent)
        return;

    fill = svgInheritParent->fill;
    stroke = svgInheritParent->stroke;
    markers = svgInheritParent->markers;
    text = svgInheritParent->text;

    svg_inherited_flags = svgInheritParent->svg_inherited_flags;
}
