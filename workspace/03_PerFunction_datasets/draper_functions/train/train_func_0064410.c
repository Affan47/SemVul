addrbook_chkparse_person(AddressBookFile *book, XMLFile *file)
{


	if (xml_parse_next_tag(file))
		longjmp(book->jumper, 1);

	if (xml_compare_tag(file, AB_ELTAG_ADDRESS_LIST))
		addrbook_chkparse_addr_list(book, file);

	if (xml_parse_next_tag(file))
		longjmp(book->jumper, 1);

	if (xml_compare_tag(file, AB_ELTAG_ATTRIBUTE_LIST))
		addrbook_chkparse_attr_list(book, file);
}
