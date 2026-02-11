Argument_process_get_option(Argument *arg,
                           gchar *string, GPtrArray *error_queue){
    register ArgumentOption *ao = NULL;
    register gint i;
    if(string[0] == '-'){
        if(string[1] == '-'){
            ao = g_tree_lookup(arg->option_registry, string+2);
            if(!ao)
                g_ptr_array_add(error_queue,
                     g_strdup_printf("Unrecognised option \"%s\"",
                                      string));
        } else {
            for(i = 1; string[i]; i++){
                ao = arg->symbol_registry[(guchar)string[i]];
                if(!ao)
                    g_error("Unknown flag [%c] in argument [%s]",
                            string[i], string);
                if(string[i+1])
                    ArgumentOption_add_value(ao, error_queue, "TRUE");
                }
            }
        }
    return ao;
    }
