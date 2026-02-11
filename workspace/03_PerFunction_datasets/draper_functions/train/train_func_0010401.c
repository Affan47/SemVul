getParameter(const string name)
{
    for (unsigned i = 0; i < mParameters.size(); i++) if (getParameter(i).getName() == name) return mParameters[i];
    return nullparam;
}
