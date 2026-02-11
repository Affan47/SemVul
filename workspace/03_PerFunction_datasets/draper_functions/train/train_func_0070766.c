setSvg(Svg *svg)
{
    if (d->svg) {
        disconnect(d->svg);
    }

    d->svg = svg;

    if (svg) {
        connect(svg, SIGNAL(repaintNeeded()), this, SLOT(svgChanged()));
    }
    update();
}
