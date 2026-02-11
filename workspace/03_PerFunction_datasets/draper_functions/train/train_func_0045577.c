HtmlLiContent(pTree, pNode, tag)
    HtmlTree *pTree;
    HtmlNode *pNode;
    int tag;
{
    if (tag==Html_LI || tag==Html_DD || tag==Html_DT) return TAG_CLOSE;
    if (tag == Html_Text || tag == Html_Space) return TAG_OK;
    return TAG_PARENT;
}
