checkSameDocument( NodeImpl *newChild, int &exceptioncode )
{
    exceptioncode = 0;
    DocumentImpl *ownerDocThis = document();
    DocumentImpl *ownerDocNew = newChild->document();
    if(ownerDocThis != ownerDocNew) {
        kDebug(6010)<< "not same document, newChild = " << newChild << "document = " << document();
        exceptioncode = DOMException::WRONG_DOCUMENT_ERR;
        return true;
    }
    return false;
}
