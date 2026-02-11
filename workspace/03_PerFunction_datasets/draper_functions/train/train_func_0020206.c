load_style_map(char *style_name) {
    mapstruct *style_map;


    for (style_map = styles; style_map != NULL; style_map = style_map->next) {
        if (!strcmp(style_name, style_map->path))
            return style_map;
    }
    style_map = load_original_map(style_name, MAP_STYLE);

    if (style_map) {
        mapstruct *tmp;

        if (style_map == first_map)
            first_map = style_map->next;
        else {
            for (tmp = first_map; tmp && tmp->next != style_map; tmp = tmp->next)
                ;
            if (tmp)
                tmp->next = style_map->next;
        }
        style_map->next = styles;
        styles = style_map;
    }
    return style_map;
}
