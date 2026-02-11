X509V3_EXT_get(X509_EXTENSION *ext)
{
	int nid;
	if((nid = OBJ_obj2nid(ext->object)) == NID_undef) return NULL;
	return X509V3_EXT_get_nid(nid);
}
