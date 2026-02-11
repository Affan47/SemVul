remove(_ThreadLocal* thread)
{
    ThreadLocals::iterator iTLocal = find( thread );
    if( iTLocal != end() )
        erase( iTLocal );
}
