CanBeReplaced()
{
    for (std::vector<NodeStatement*>::iterator it = statements.begin(); it != statements.end(); ++it)
        if (!(*it)->CanBeReplaced()) return false;
    return true;
}
