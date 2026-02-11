clearTree(clustalw::TreeNode* p)
{
    clearTreeNodes(p);
    delete [] nptr;
    nptr  = NULL;
    delete [] ptrs;
    ptrs  = NULL;
    delete [] lptr;
    lptr  = NULL;
    delete [] olptr;
    olptr  = NULL;
}
