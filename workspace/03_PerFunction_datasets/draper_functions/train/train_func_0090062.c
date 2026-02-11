handleURI(URI& uri)
{
    checkHandlerListSorted();
    for (std::list<URIHandler*>::iterator it = handlersM.begin(); it != handlersM.end(); ++it)
        if ((*it)->handleURI(uri))
            return true;
    return false;
}
