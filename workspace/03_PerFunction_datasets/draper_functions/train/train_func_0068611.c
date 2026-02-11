PercentageOfViewport(float value, const SVGStyledElement* context, SVGLengthMode mode)
{
    ASSERT(context);

    float width = 0.0f, height = 0.0f;
    SVGElement* viewportElement = context->viewportElement();

    Document* doc = context->document();
    if (doc->documentElement() == context) {

        RenderView* view = static_cast<RenderView*>(doc->renderer());
        if (view && view->view()) {
            width = view->view()->visibleWidth();
            height = view->view()->visibleHeight();
         }
    } else if (viewportElement && viewportElement->isSVG()) {
        const SVGSVGElement* svg = static_cast<const SVGSVGElement*>(viewportElement);
        if (svg->hasAttribute(SVGNames::viewBoxAttr)) {
            width = svg->viewBox().width();
            height = svg->viewBox().height();
        } else {
            width = svg->width().value();
            height = svg->height().value();
        }
    } else if (context->parent() && !context->parent()->isSVGElement()) {
        if (RenderObject* renderer = context->renderer()) {
            width = renderer->width();
            height = renderer->height();
        }
    }

    if (mode == LengthModeWidth)
        return value * width;
    else if (mode == LengthModeHeight)
        return value * height;
    else if (mode == LengthModeOther)
        return value * sqrtf(powf(width, 2) + powf(height, 2)) / sqrtf(2.0f);

    return 0.0f;
}
