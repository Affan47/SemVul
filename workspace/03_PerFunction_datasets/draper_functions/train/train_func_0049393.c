icalparser_free(icalparser* parser)
{
    struct icalparser_impl* impl = (struct icalparser_impl*)parser;
    icalcomponent *c;

    if (impl->root_component != 0){
	icalcomponent_free(impl->root_component);
    }

    while( (c=pvl_pop(impl->components)) != 0){
	icalcomponent_free(c);
    }

    pvl_free(impl->components);

    free(impl);
}
