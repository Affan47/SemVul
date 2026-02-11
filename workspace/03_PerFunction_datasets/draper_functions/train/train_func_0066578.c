eventListener(int *type, ...) {
    int rv = 0;
    va_list args;
    object *who;
    int event_code;
    object *activator;

    object *event;


    object *newspaper;
    paper_properties *paper;
    region *reg;

    va_start(args, type);
    who = va_arg(args, object *);

    activator = va_arg(args, object *);
     va_arg(args, object *);
     va_arg(args, char *);
     va_arg(args, int);

    event = va_arg(args, object *);
    event_code = event->subtype;

    va_end(args);

    if (event_code != EVENT_APPLY)
        return rv;

    paper = get_newspaper(event->slaying);

    newspaper = cf_create_object_by_name("scroll");

    cf_object_set_string_property(newspaper, CFAPI_OBJECT_PROP_NAME, paper->name);
    cf_object_set_string_property(newspaper, CFAPI_OBJECT_PROP_NAME_PLURAL, paper->name);

    if (activator->map)
        reg = cf_map_get_region_property(activator->map, CFAPI_MAP_PROP_REGION);
    else
        reg = NULL;

    get_newspaper_content(newspaper, paper, reg);

    cf_object_insert_object(newspaper, who);

    return rv;
}
