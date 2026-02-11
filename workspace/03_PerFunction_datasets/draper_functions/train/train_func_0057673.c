unmark_symbols_(jl_sym_t *root)
{
    while (root != NULL) {
        root->type = (jl_type_t*)(((uptrint_t)root->type)&~1UL);
        unmark_symbols_(root->left);
        root = root->right;
    }
}
