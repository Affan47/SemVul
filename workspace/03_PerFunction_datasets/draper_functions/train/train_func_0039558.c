InteractWith( eGameObject * target, REAL time, int recursion )
{
    gCycle* prey = dynamic_cast< gCycle* >( target );
    if ( prey )
    {
        REAL r = this->Radius();
        if ( ( prey->Position() - this->Position() ).NormSquared() < r*r )
        {
            if ( prey->Player() && prey->Alive() )
            {
                OnEnter( prey, time );
            }
        }
    }
}
