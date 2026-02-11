simplifyOrthogonalRoutes(Router *router)
{

    for (ConnRefList::const_iterator curr = router->connRefs.begin();
            curr != router->connRefs.end(); ++curr)
    {
        if ((*curr)->routingType() != ConnType_Orthogonal)
        {
            continue;
        }
        (*curr)->set_route((*curr)->displayRoute().simplify());
    }
}
