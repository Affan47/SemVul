tack_shift_bad(tack_t *stack) {
    return (stack == NULL || stack->pos >= stack->len);
}
