start_buffer(void)
{
    stk.last++;
    stk.last->buf = (char *)malloc(BUF_INIT_SIZE);
    check_mem(stk.last->buf);
    stk.last->cur = stk.last->buf;
    stk.last->size = BUF_INIT_SIZE;
    if (stk.last == stk.end) resize_buffer_stack();
}
