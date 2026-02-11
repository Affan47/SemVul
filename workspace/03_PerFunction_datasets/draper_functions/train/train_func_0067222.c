locate_data(struct Wrapper *wrapper, int height)
{
    if (wrapper->node->left)
        parse_data(wrapper, wrapper->node->left, height);

    if (wrapper->node->right)
        parse_data(wrapper, wrapper->node->right, height);
}
