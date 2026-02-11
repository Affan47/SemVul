processNext()
{
    RoutingRule *rule=getNext(); if (rule==NULL) return false;
    tmp_queue.push_back(rule);

    RuleElementRItf *itfrel = rule->getRItf();

    if (itfrel->isAny()) return true;

    FWObject *o = FWReference::cast(itfrel->front())->getPointer();


    Interface *iface = Interface::cast(o);
    if (iface)
    {
        FWObject *parent = Host::getParentHost(iface);

        if (parent->getId() == compiler->fw->getId()) return true;

        Cluster *cluster = Cluster::cast(parent);
        if (cluster)
        {
            list<Firewall*> members;
            cluster->getMembersList(members);
            list<Firewall*>::iterator it;
            for (it=members.begin(); it!=members.end(); ++it)
            {
                if ((*it)->getId() == compiler->fw->getId()) return true;
            }
        }
    }
    string msg;
    msg = "Object \"" + o->getName() +
        "\" used as interface in the routing rule " +
        rule->getLabel() +
        " is not a child of the firewall the rule belongs to";
    compiler->abort(rule, msg.c_str());


    return true;
}
