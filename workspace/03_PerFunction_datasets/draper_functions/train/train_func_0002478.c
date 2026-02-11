deepCompareDomNodes(const QDomNode & node1, const QDomNode & node2)
{


    if (node1.nodeName() != node2.nodeName() || node1.nodeValue() != node2.nodeValue())
        return false;


    const QDomNodeList node1Children  = node1.childNodes();
    const QDomNodeList node2Children  = node2.childNodes();

    if (node1Children.count () != node2Children.count ())
        return false;

    for (int i=0; i<node1Children.count ();i++) {
        if (!deepCompareDomNodes(node1Children.at(i), node2Children.at(i) ))
            return false;
    }
    return true;
}
