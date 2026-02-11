removeTechnique(size_t index)
{
    assert (index < mTechniques.size() && "Index out of bounds.");
    Techniques::iterator i = mTechniques.begin() + index;
    OGRE_DELETE (*i);
    mTechniques.erase(i);
    mSupportedTechniques.clear();
    mCompilationRequired = true;
}
