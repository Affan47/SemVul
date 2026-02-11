hattrie_iter_nextnode(hattrie_iter_t* i)
{
    if (i->stack == NULL) return;


    node_ptr node;
    hattrie_node_stack_t* next;
    unsigned char   c;
    size_t level;

    node  = i->stack->node;
    next  = i->stack->next;
    c     = i->stack->c;
    level = i->stack->level;

    free(i->stack);
    i->stack = next;

    if (*node.flag & NODE_TYPE_TRIE) {
        hattrie_iter_pushchar(i, level, c);

        if(node.t->flag & NODE_HAS_VAL) {
            i->has_nil_key = true;
            i->nil_val = node.t->val;
        }


        int j;
        for (j = TRIE_MAXCHAR; j >= 0; --j) {


            if (j < TRIE_MAXCHAR && node.t->xs[j].t == node.t->xs[j + 1].t) continue;


            next = i->stack;
            i->stack = malloc(sizeof(hattrie_node_stack_t));
            i->stack->node  = node.t->xs[j];
            i->stack->next  = next;
            i->stack->level = level + 1;
            i->stack->c     = (unsigned char) j;
        }
    }
    else {
        if (*node.flag & NODE_TYPE_PURE_BUCKET) {
            hattrie_iter_pushchar(i, level, c);
        }
        else {
            i->level = level - 1;
        }

        i->i = malloc(sizeof(hhash_iter_t));
        hhash_iter_begin(node.b, i->i, i->sorted);
    }
}
