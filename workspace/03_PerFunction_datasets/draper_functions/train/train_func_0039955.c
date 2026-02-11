executeTextQuery(const SVGTextContentElement* element, SVGInlineTextBoxQueryWalker::QueryMode mode,
                                                           long startPosition = 0, long length = 0, FloatPoint referencePoint = FloatPoint())
{
    SVGRootInlineBox* rootBox = rootInlineBoxForTextContentElement(element);
    if (!rootBox)
        return SVGInlineTextBoxQueryWalker(0, mode);


    Vector<SVGInlineTextBox*> textBoxes = findInlineTextBoxInTextChunks(element, rootBox->svgTextChunks());


    SVGInlineTextBoxQueryWalker walkerCallback(element, mode);
    walkerCallback.setQueryInputParameters(startPosition, length, referencePoint);

    SVGTextChunkWalker<SVGInlineTextBoxQueryWalker> walker(&walkerCallback, &SVGInlineTextBoxQueryWalker::chunkPortionCallback);

    Vector<SVGInlineTextBox*>::iterator it = textBoxes.begin();
    Vector<SVGInlineTextBox*>::iterator end = textBoxes.end();

    for (; it != end; ++it) {
        rootBox->walkTextChunks(&walker, *it);

        if (walkerCallback.stopProcessing())
            break;
    }

    return walkerCallback;
}
