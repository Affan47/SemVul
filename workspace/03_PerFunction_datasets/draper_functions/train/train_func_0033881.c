createStroke(stroke_t ** pStroke, INT64 allocatedSize, stroke_t * next,
        drawAttrs_t * drawAttrs)
{
    int err = OK;
    stroke_t * ptrS = (stroke_t *) malloc(sizeof(stroke_t));

    if (ptrS)
    {
        ptrS->xOrigin = ptrS->yOrigin = INT64_MAX;
        ptrS->xEnd = ptrS->yEnd = INT64_MIN;
        ptrS->next = next;
        ptrS->P = NULL;
        ptrS->drawAttrs = drawAttrs;
        ptrS->nPoints = 0;
        if (allocatedSize)
            ptrS->allocatedSize = allocatedSize;
        else
            ptrS->allocatedSize = DEFAULT_STROKE_SIZE;

        ptrS->X = malloc (ptrS->allocatedSize * sizeof(INT64));
        if(!ptrS->X)
        {
            free(ptrS);
            ptrS = NULL;
            *pStroke = NULL;
            err = OUT_OF_MEMORY;
        }
        ptrS->Y = malloc (ptrS->allocatedSize * sizeof(INT64));
        if(!ptrS->Y)
        {
            free(ptrS->X);
            free(ptrS);
            ptrS = NULL;
            *pStroke = NULL;
            err = OUT_OF_MEMORY;
        }
    } else {
        err = OUT_OF_MEMORY;
    }
    *pStroke = ptrS;
    return err;
}
