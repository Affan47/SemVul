removeParameter(UniformParameterPtr parameter)
{
    UniformParameterIterator it;

    for (it = mParameters.begin(); it != mParameters.end(); ++it)
    {
        if ((*it) == parameter)
        {
            (*it).setNull();
            mParameters.erase(it);
            break;
        }
    }
}
