Reset()
{
    numChild = 0;
    id = -1;
    if ( name ) {
        delete [] name;
        name = 0;
    }
}
