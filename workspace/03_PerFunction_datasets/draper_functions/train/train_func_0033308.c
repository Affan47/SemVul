markStack(int mark_soft_refs) {
    while(mark_stack_count > 0) {
        Object *object = mark_stack[--mark_stack_count];
        int mark = IS_MARKED(object);

        markChildren(object, mark, mark_soft_refs);
    }
}
