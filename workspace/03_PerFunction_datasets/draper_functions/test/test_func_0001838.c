destroyDefaultProgramWriterFactories()
{
    for (unsigned int i=0; i<mProgramWriterFactories.size(); i++)
    {
        ProgramWriterManager::getSingletonPtr()->removeFactory(mProgramWriterFactories[i]);
        OGRE_DELETE mProgramWriterFactories[i];
    }
    mProgramWriterFactories.clear();
}
