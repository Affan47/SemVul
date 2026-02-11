calcViewport()
{
    SVGElement* svgelem = static_cast<SVGElement*>(element());
    if (svgelem->hasTagName(SVGNames::svgTag)) {
        SVGSVGElement* svg = static_cast<SVGSVGElement*>(element());

        if (!selfNeedsLayout() && !svg->hasRelativeValues())
            return;

		float w, h;
        SVGLength width = svg->width();
        if (width.unitType() == LengthTypePercentage && svg->hasSetContainerSize())
            w = svg->relativeWidthValue();
        else
            w = width.value();

        SVGLength height = svg->height();
        if (height.unitType() == LengthTypePercentage && svg->hasSetContainerSize())
            h = svg->relativeHeightValue();
        else
            h = height.value();
        m_viewport = FloatRect(0, 0, w, h);
    }
}
