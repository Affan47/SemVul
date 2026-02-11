addGroup( const string &groupName, int groupSize)
{
    XTRACE();
    ParticleGroup *newGroup = new ParticleGroup( groupName, groupSize);
    newGroup->init();
    _particleGroupMap[ groupName] = newGroup;


    _particleGroupList.insert( _particleGroupList.end(), newGroup);

    LOG_INFO << "Adding Particle Group [" << groupName << "]" << endl;
}
