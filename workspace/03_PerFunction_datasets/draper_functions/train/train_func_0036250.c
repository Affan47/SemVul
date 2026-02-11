ownerDocument() const
{


    DocumentImpl* doc = document();
    if (doc == this)
        return 0;
    else
        return doc;
}
