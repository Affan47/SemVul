try_remove_classifiers(RouterT *router, Vector<ElementT *> &classifiers)
{
    for (int i = 0; i < classifiers.size(); i++)
	if (!router->find_connections_to(PortT(classifiers[i], 0))) {
	    classifiers[i]->kill();
	    classifiers[i] = classifiers.back();
	    classifiers.pop_back();
	    i--;
	}
    router->remove_dead_elements();
}
