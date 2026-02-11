xmlSecKeyGetData(xmlSecKeyPtr key, xmlSecKeyDataId dataId) {

    xmlSecAssert2(key != NULL, NULL);
    xmlSecAssert2(dataId != xmlSecKeyDataIdUnknown, NULL);


    if(dataId == xmlSecKeyDataValueId) {
	return(key->value);
    } else if(key->dataList != NULL) {
	xmlSecKeyDataPtr tmp;
	xmlSecSize pos, size;

	size = xmlSecPtrListGetSize(key->dataList);
	for(pos = 0; pos < size; ++pos) {
	    tmp = (xmlSecKeyDataPtr)xmlSecPtrListGetItem(key->dataList, pos);
	    if((tmp != NULL) && (tmp->id == dataId)) {
		return(tmp);
	    }
	}
    }
    return(NULL);
}
