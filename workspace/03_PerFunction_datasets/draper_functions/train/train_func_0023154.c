addStringAttr(DcmItem *item, const DcmTagKey& key, const SimpleStr& str)
{
    OFCondition ec = EC_Normal;
    DcmTag tag(key);
    DcmElement *newElement = NULL;

    if (item == NULL) {
	CERR << "error: cannot add to null item" << OFendl;
	return OFFalse;
    }

    ec = newDicomElement(newElement, tag);
    if (ec != EC_Normal) {
	CERR << "error: cannot create element: " << key << OFendl;
	return OFFalse;
    }

    ec = newElement->putString(str.c_str());
    if (ec != EC_Normal) {
	CERR << "error: cannot put element value: " << key << OFendl;
	return OFFalse;
    }

    ec = item->insert(newElement, OFTrue);
    if (ec != EC_Normal) {
	CERR << "error: cannot insert element: " << key << OFendl;
	return OFFalse;
    }

    return OFTrue;
}
