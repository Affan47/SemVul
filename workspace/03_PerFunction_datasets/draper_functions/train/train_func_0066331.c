gf_svg_get_property_pointer(SVG_Element *elt, void *input_attribute,
								   SVGPropertiesPointers *output_property_context)
{
	SVGAttribute *att = elt->attributes;
	while (att) {
		if (att->data == input_attribute) break;
		att = att->next;
	}
	if (!att) return NULL;
	return gf_svg_get_property_pointer_from_tag(output_property_context, att->tag);
}
