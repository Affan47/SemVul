gotoNamedNode(const DSRCodedEntryValue &conceptName,
                                      const OFBool startFromRoot,
                                      const OFBool searchIntoSub)
{
    size_t nodeID = 0;
    if (conceptName.isValid())
    {
        if (startFromRoot)
            gotoRoot();
        DSRDocumentTreeNode *node = NULL;
        clearNodeCursorStack();

        do {
            node = OFstatic_cast(DSRDocumentTreeNode *, getNode());
            if ((node != NULL) && (node->getConceptName() == conceptName))
                nodeID = node->getNodeID();
        } while ((nodeID == 0) && iterate(searchIntoSub));
    }
    return nodeID;
}
