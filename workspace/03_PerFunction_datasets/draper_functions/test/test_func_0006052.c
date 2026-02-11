soap_out_wsa__Relationship(struct soap *soap, const char *tag, int id, const struct wsa__Relationship *a, const char *type)
{
	if (a->RelationshipType)
		soap_set_attr(soap, "RelationshipType", soap_QName2s(soap, a->RelationshipType), 1);
	if (a->__anyAttribute)
		soap_set_attr(soap, "-anyAttribute", a->__anyAttribute, 1);
	(void)soap; (void)tag; (void)id; (void)type;
	return soap_out_string(soap, tag, id, &a->__item, "");
}
