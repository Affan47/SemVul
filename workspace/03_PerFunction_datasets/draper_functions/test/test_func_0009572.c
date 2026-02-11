ClearCGroup()

{
    for( int i = 0; apoCGroup[i] != NULL; i++ )
        delete apoCGroup[i];

    apoCGroup[0] = NULL;
    apoCGroup[1] = NULL;
}
