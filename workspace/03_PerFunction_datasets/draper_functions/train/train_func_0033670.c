propertyValuesSetAutoInteger(p, pProp, piVal)
    HtmlComputedValuesCreator *p;
    CssProperty *pProp;
    int *piVal;
{
    if (pProp->eType == CSS_TYPE_FLOAT) {
        *piVal = (int)pProp->v.rVal;
    }else if (pProp->eType == CSS_CONST_AUTO) {
        *piVal = PIXELVAL_AUTO;
    }else{

        return 1;
    }
    return 0;
}
