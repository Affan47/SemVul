innerText() const
{
    QString text = "";
    if(!firstChild())
        return text;

    const NodeImpl *n = this;

    while(n) {
        if(n->firstChild())
            n = n->firstChild();
        else if(n->nextSibling())
            n = n->nextSibling();
        else {
            NodeImpl *next = 0;
            while(!next) {
                n = n->parentNode();
                if(!n || n == (NodeImpl *)this ) goto end;
                next = n->nextSibling();
            }
            n = next;
        }
        if(n->isTextNode() ) {
            DOMStringImpl* data = static_cast<const TextImpl *>(n)->string();
            text += QString::fromRawData(data->s, data->l);
        }
    }
 end:
    return text;
}
