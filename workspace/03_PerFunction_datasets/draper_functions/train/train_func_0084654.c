FreeTree(XmtHelpTree *node)
#else
static void FreeTree(node)
XmtHelpTree *node;
#endif
{
    int i;

    if (!node) return;

    for(i=0; i < node->num_children; i++)
	FreeTree(node->children[i]);

    XtFree((char *)node->children);
    XtFree((char *)node->crossrefs);
    XmStringFree(node->title);
    XtFree((char *)node);
}
