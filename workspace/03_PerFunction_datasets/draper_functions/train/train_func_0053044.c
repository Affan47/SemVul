icalparser_parse(icalparser *parser,
				char* (*line_gen_func)(char *s, size_t size,
						       void* d))
{

    char* line;
    icalcomponent *c=0;
    icalcomponent *root=0;
    icalerrorstate es = icalerror_get_error_state(ICAL_MALFORMEDDATA_ERROR);

    icalerror_check_arg_rz((parser !=0),"parser");

    icalerror_set_error_state(ICAL_MALFORMEDDATA_ERROR,ICAL_ERROR_NONFATAL);

    do{
	    line = icalparser_get_line(parser, line_gen_func);

	if ((c = icalparser_add_line(parser,line)) != 0){

	    if(icalcomponent_get_parent(c) !=0){

	    }

	    assert(impl->root_component == 0);
	    assert(pvl_count(impl->components) ==0);

	    if (root == 0){

		root = c;
	    } else if(icalcomponent_isa(root) != ICAL_XROOT_COMPONENT) {


		icalcomponent *tempc = icalcomponent_new(ICAL_XROOT_COMPONENT);
		icalcomponent_add_component(tempc, root);
		icalcomponent_add_component(tempc, c);
		root = tempc;
	    } else if(icalcomponent_isa(root) == ICAL_XROOT_COMPONENT) {


		icalcomponent_add_component(root, c);

	    } else {

		assert(0);
	    }

	    c = 0;

        }
	if(line != 0){
	    free(line);
	}
    } while ( line != 0);

    icalerror_set_error_state(ICAL_MALFORMEDDATA_ERROR,es);

    return root;

}
