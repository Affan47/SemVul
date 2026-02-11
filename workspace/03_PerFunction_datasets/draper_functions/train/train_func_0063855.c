read_VlKDTree(FILE *fp, VlKDForest * self, VlKDTree *tree)
{
    size_t n = 0;
    vl_size i;

    n += fread(&(tree->numUsedNodes), sizeof(vl_size), 1, fp);
    n += fread(&(tree->numAllocatedNodes), sizeof(vl_size), 1, fp);
    n += fread(&(tree->depth), sizeof(unsigned int), 1, fp);

    tree->nodes = vl_malloc(sizeof(VlKDTreeNode) * tree->numAllocatedNodes);
    for(i = 0;i < tree->numAllocatedNodes; i++){
        n += read_VlKDTreeNode(fp, &tree->nodes[i]);
    }

    tree->dataIndex = vl_malloc(sizeof(VlKDTreeDataIndexEntry) * self->numData);
    for(i = 0;i < self->numData ; i++){
        n += read_VlKDTreeDataIndexEntry(fp, &tree->dataIndex[i]);
    }

    return n;
}
