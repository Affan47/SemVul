camel_header_address_add_member (struct _camel_header_address *h,
                                 struct _camel_header_address *member)
{
	if (h) {
		if (h->type == CAMEL_HEADER_ADDRESS_GROUP
		    || h->type == CAMEL_HEADER_ADDRESS_NONE) {
			h->type = CAMEL_HEADER_ADDRESS_GROUP;
			camel_header_address_list_append (&h->v.members, member);
		}
	}
}
