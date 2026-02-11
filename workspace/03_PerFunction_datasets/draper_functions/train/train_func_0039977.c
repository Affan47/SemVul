layoutreader_element_open(struct layout *layout, char *name)
{
	START_FUNC
	if (name) while (layout->cur && xmlStrcmp(layout->cur->name, (xmlChar *)name))
		layout->cur=layout->cur->next;
	if (layout->cur) layout->cur=layout->cur->children;
	END_FUNC
	return layout->cur==NULL?FALSE:TRUE;
}
