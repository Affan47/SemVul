addLink( const string &group1, const string &group2)
{
    XTRACE();

    ParticleGroup *g1 = getParticleGroup( group1);
    ParticleGroup *g2 = getParticleGroup( group2);

    if( !g1 || !g2) return;

    LOG_INFO << "Collision detection between ["
             << group1 << "] and ["
             << group2 << "] enabled."
             << endl;

    LinkedParticleGroup *lpg = new LinkedParticleGroup;
    lpg->group1 = g1;
    lpg->group2 = g2;

    _linkedParticleGroupList.insert( _linkedParticleGroupList.end(), lpg);
}
