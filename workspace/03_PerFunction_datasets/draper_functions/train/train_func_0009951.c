peel_loop(Block *loop, Block *next_block)
{
    Block *head;
    Block *tail;

    head = copy_loop_statements_to_body(loop);

    for (tail = head; tail->next != NULL; tail = tail->next) ;

    tail->next = next_block;
    if (next_block != NULL)
        next_block->prev = tail;
    set_mt_num(head, loop->no - 1);

    return head;
}
