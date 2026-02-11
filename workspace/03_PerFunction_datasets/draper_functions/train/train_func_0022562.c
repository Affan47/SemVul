flush_module(void)
{
    if (mstack.index == 0) return 0;
    yy_delete_buffer(YY_CURRENT_BUFFER);
    yy_switch_to_buffer(mstack.buffer[--mstack.index]);
    return 1;
}
