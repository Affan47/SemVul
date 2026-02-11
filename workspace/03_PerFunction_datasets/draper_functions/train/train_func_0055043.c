CountLeaves(TreeNode tree, int *n)
{
    if (tree->leaf)
    {
        *n = *n + 1;
    }
    else
    {
        int i;
        TreeNode child;

        for (i = 0; i < 8; i++)
            if (NULL != (child = tree->kids[i]))
                if (! CountLeaves(child, n))
                    return ERROR;
    }

    return OK;
}
