calcWeight(int leaf)
{
    clustalw::TreeNode* p;
    float weight = 0.0;

    p = olptr[leaf];
    while (p->parent != NULL)
    {
        weight += p->dist / p->order;
        p = p->parent;
    }

    weight *= 100.0;

    return ((int)weight);
}
