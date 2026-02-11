findTaskByName(const TaskArray& a, const std::string& nm)
{
    for (unsigned int t=0; t < a.size(); ++t)
    {
        if (a[t]->name() == nm) return t;
    }

    return -1;
}
