prcWrite(pfPrcHelper* prc) {
    prc->startTag("plSpaceTreeNode");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Parent", fParent);
    if (fFlags & kIsLeaf) {
        prc->writeParam("LeafIndex", fLeafIndex);
    } else {
        prc->writeParam("LeftChild", fChildren[0]);
        prc->writeParam("RightChild", fChildren[1]);
    }
    prc->endTag();
    fWorldBounds.prcWrite(prc);
    prc->closeTag();
}
