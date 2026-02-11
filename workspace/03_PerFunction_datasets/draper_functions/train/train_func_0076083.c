astnode_create_storage(astnode *type, astnode *count, location loc)
{
    astnode *n = astnode_create(STORAGE_NODE, loc);

    astnode_add_child(n, type);

    if (count == NULL) {

        count = astnode_create_integer(1, loc);
    }
    astnode_add_child(n, count);
    return n;
}
