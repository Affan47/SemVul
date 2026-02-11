addLeaf(const hsBounds3Ext& bounds) {
    plSpaceTreeNode node;
    node.setLeafIndex(fNumLeaves);
    node.setBounds(bounds);
    fTree.append(node);
    fNumLeaves++;
    return fTree.getSize() - 1;
}
