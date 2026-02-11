verify_redblack(dnode_t *nil, dnode_t *root)
{
    unsigned height_left, height_right;

    if (root != nil) {
        height_left = verify_redblack(nil, root->left);
        height_right = verify_redblack(nil, root->right);
        if (height_left == 0 || height_right == 0)
            return 0;
        if (height_left != height_right)
            return 0;
        if (root->color == dnode_red) {
            if (root->left->color != dnode_black)
                return 0;
            if (root->right->color != dnode_black)
                return 0;
            return height_left;
        }
        if (root->color != dnode_black)
            return 0;
        return height_left + 1;
    }
    return 1;
}
