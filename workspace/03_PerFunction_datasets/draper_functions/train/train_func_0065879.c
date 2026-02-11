getAliveCount( void)
{
    XTRACE();
    int total = 0;
    list<ParticleGroup*>::iterator i;
    for( i=_particleGroupList.begin(); i!=_particleGroupList.end(); i++)
    {
        total += (*i)->getAliveCount();
    }
    return total;
}
