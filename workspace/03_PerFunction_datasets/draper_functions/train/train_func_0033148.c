show(AW_device *device)
{
    long parsval = 0;
    if (GLOBAL_NT->tree->tree_root) parsval = (long)GLOBAL_NT->tree->tree_root->costs();
    GLOBAL_NT->awr->awar(AWAR_PARSIMONY)->write_int( parsval);
    long best = GLOBAL_NT->awr->awar(AWAR_BEST_PARSIMONY)->read_int();
    if (parsval < best || 0==best) {
        GLOBAL_NT->awr->awar(AWAR_BEST_PARSIMONY)->write_int( parsval);
    }
    this->AWT_graphic_tree::show(device);
}
