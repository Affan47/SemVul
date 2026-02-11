X509_ATTRIBUTE_create_by_OBJ(X509_ATTRIBUTE **attr,
	     const ASN1_OBJECT *obj, int atrtype, const void *data, int len)
{
	X509_ATTRIBUTE *ret;

	if ((attr == NULL) || (*attr == NULL))
		{
		if ((ret=X509_ATTRIBUTE_new()) == NULL)
			{
			X509err(X509_F_X509_ATTRIBUTE_CREATE_BY_OBJ,ERR_R_MALLOC_FAILURE);
			return(NULL);
			}
		}
	else
		ret= *attr;

	if (!X509_ATTRIBUTE_set1_object(ret,obj))
		goto err;
	if (!X509_ATTRIBUTE_set1_data(ret,atrtype,data,len))
		goto err;

	if ((attr != NULL) && (*attr == NULL)) *attr=ret;
	return(ret);
err:
	if ((attr == NULL) || (ret != *attr))
		X509_ATTRIBUTE_free(ret);
	return(NULL);
}
