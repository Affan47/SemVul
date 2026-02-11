printPrimerLists ()
{
    int count = 0;

    printf( "printPrimerLists : list 1 : [(start_pos,offset,length), GC_ratio, temperature]\n" );
    Item *current = list1;
    while ( current != NULL ) {
        current->print( "","\n" );
        current = current->next;
        count++;
    }
    printf( " : %i valid primers\nprintPrimerLists : list 2 : [(start_pos,offset,length), GC_ratio, temperature]\n", count );
    count = 0;
    current = list2;
    while ( current != NULL ) {
        current->print( "","\n" );
        current = current->next;
        count++;
    }
    printf( " : %i valid primers\n", count );
}
