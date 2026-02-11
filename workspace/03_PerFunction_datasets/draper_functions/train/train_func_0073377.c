idIsUnique(const unsigned int id) const
{
    unsigned int count = 0;


    for (ShapeRefList::const_iterator i = shapeRefs.begin();
            i != shapeRefs.end(); ++i)
    {
        if ((*i)->id() == id)
        {
            count++;
        }
    }


    for (ConnRefList::const_iterator i = connRefs.begin();
            i != connRefs.end(); ++i)
    {
        if ((*i)->id() == id)
        {
            count++;
        }
    }


    for (ClusterRefList::const_iterator i = clusterRefs.begin();
            i != clusterRefs.end(); ++i)
    {
        if ((*i)->id() == id)
        {
            count++;
        }
    }

    if (count > 1)
    {
        db_printf("Warning:\tlibavoid object ID %d not unique.\n", id);
        return false;
    }
    return true;
}
