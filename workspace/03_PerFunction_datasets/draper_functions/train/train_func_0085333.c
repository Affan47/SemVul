main() {
    char mainStack[64];
    struct co_context* mainCtx = co_create(0, 0, mainStack, sizeof(mainStack));

    int i;
    for (i=0; i<THREAD_COUNT; i++) {
        char* stack = malloc(STACK_SIZE);
        printf("stack: %p\n", stack);
        ctxs[i] = co_create(test, (void*)(size_t)i, stack, STACK_SIZE);

    }
    co_transfer(mainCtx, ctxs[0]);
    return 0;
}
