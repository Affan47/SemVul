HtmlHashInit(htmlPtr, start)
    void *htmlPtr;
    int start;
{
    static int isInit = 0;

    int i;
    int h;

    if (isInit) return;

    for (i = start; i < HTML_MARKUP_COUNT; i++) {
        h = HtmlHash(htmlPtr, HtmlMarkupMap[i].zName);
        HtmlMarkupMap[i].pCollide = apMap[h];
        apMap[h] = &HtmlMarkupMap[i];
    }
#ifdef TEST
    HtmlHashStats(htmlPtr);
#endif

    isInit = 1;
}
