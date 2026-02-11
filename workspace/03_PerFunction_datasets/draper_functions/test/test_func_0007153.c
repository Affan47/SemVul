absoluteRects(Vector<IntRect>& rects, int, int)
{
    InlineRunBox* firstBox = firstLineBox();

    SVGRootInlineBox* rootBox = firstBox ? static_cast<SVGInlineTextBox*>(firstBox)->svgRootInlineBox() : 0;
    RenderObject* object = rootBox ? rootBox->object() : 0;

    if (!object)
        return;

    int xRef = object->xPos() + xPos();
    int yRef = object->yPos() + yPos();

    for (InlineRunBox* curr = firstBox; curr; curr = curr->nextLineBox()) {
        FloatRect rect(xRef + curr->xPos(), yRef + curr->yPos(), curr->width(), curr->height());
        rects.append(enclosingIntRect(absoluteTransform().mapRect(rect)));
    }
}
