complexMatch(Address *obj1, Address *obj2)
{
    if (obj1->getId()==obj2->getId()) return true;

    if (Cluster::cast(obj1) && Firewall::cast(obj2))
    {


        int cluster_id = obj2->getInt("parent_cluster_id");
        if (obj1->getId() == cluster_id) return true;
    }

    void* res = obj1->dispatch(this, obj2);
    return (res != NULL);
}
