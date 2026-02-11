markerBoxLayout(pLayout, pBox, pNode, pVerticalOffset)
    LayoutContext *pLayout;
    HtmlNode *pNode;
    BoxContext *pBox;
    int *pVerticalOffset;
{
    HtmlComputedValues *pComputed = HtmlNodeComputedValues(pNode);
    int mmt = pLayout->minmaxTest;
    int voffset = 0;

    if (
        0 == pComputed->imListStyleImage &&
        pComputed->eListStyleType == CSS_CONST_NONE
    ) {
        return 0;
    }

    if (pComputed->imListStyleImage) {
        HtmlImage2 *pImg = pComputed->imListStyleImage;
        int iWidth = PIXELVAL_AUTO;
        int iHeight = PIXELVAL_AUTO;
        pImg = HtmlImageScale(pComputed->imListStyleImage, &iWidth, &iHeight,1);

        HtmlDrawImage(
            &pBox->vc, pImg, 0, -1 * iHeight, iWidth, iHeight, pNode, mmt
        );
        HtmlImageFree(pImg);
        pBox->width = iWidth;
        pBox->height = iHeight;
    } else {
        HtmlCanvas *pCanvas = &pBox->vc;
        int eStyle;
        Tk_Font font;
        char zBuf[128];
        int iList = 1;

        HtmlNode *pParent = HtmlNodeParent(pNode);
        eStyle = pComputed->eListStyleType;


        if (pParent) {
            int ii;
            int iStart = HtmlNodeComputedValues(pParent)->iOrderedListStart;
            if (iStart != PIXELVAL_AUTO) {
                iList = iStart;
            }
            for (ii = 0; ii < HtmlNodeNumChildren(pParent); ii++) {
                HtmlNode *pSibling = HtmlNodeChild(pParent, ii);
                HtmlComputedValues *pSibProp = HtmlNodeComputedValues(pSibling);
                if (pSibling == pNode) {
                    break;
                }
                if (DISPLAY(pSibProp) == CSS_CONST_LIST_ITEM) {
                    iList++;
                    if (pSibProp->iOrderedListValue != PIXELVAL_AUTO) {
                        iList = pSibProp->iOrderedListValue;
                    }
                }
            }
        }
        if (pComputed->iOrderedListValue != PIXELVAL_AUTO) {
            iList = pComputed->iOrderedListValue;
        }

        HtmlLayoutMarkerBox(eStyle, iList, 1, zBuf);

        font = pComputed->fFont->tkfont;

        pBox->height = voffset + pComputed->fFont->metrics.descent;
        pBox->width = Tk_TextWidth(font, zBuf, strlen(zBuf));

        HtmlDrawText(
            pCanvas, zBuf, strlen(zBuf), 0, voffset, pBox->width, mmt, pNode, -1
        );
    }

    pBox->width += pComputed->fFont->ex_pixels;
    *pVerticalOffset = voffset;
    return 1;
}
