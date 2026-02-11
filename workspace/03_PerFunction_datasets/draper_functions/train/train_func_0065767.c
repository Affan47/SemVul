Alive ( ) const
{
    for (int i= players.Len()-1; i>=0; --i)
    {
        ePlayerNetID* p = players(i);
        if ( p->Object() && p->Object()->Alive() )
        {
            return true;
        }
    }

    return false;
}
