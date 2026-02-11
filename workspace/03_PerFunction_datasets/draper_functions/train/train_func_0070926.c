print_tdop_list( tdop *head, size_t depth )
{
    int j,k;

    if ( !head ) {
        jprintf( depth, "EMPTY\n" );
        return;
    }

    while ( head ) {
        jprintf( depth, "Pointer - 0x%08lx\n",
                head->point );
        jprintf( depth, "Token --- %d\n",
                (unsigned short)head->tok );

        head = head->link;
    }
}
