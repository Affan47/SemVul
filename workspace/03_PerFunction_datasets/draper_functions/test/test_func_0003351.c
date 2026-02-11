compiler_next_block(struct compiler *c)
{
    basicblock *block = compiler_new_block(c);
    if (block == NULL)
        return NULL;
    c->u->u_curblock->b_next = block;
    c->u->u_curblock = block;
    return block;
}
