Argument_usage(Argument *arg, gchar *synopsis){
    register ArgumentOption *ao;
    register gint i;
    Argument_show_version(arg);
    g_print("\n%s: %s\n", arg->name, arg->desc);
    if(synopsis){
        g_print("%s\n", synopsis);
    } else {
        g_print("Synopsis:\n--------\n%s", arg->name);
        for(i = 0; i < arg->mandatory_set->len; i++){
            ao = arg->mandatory_set->pdata[i];
            g_print(" <%s>", ao->type);
            }
        g_print("\n\n");
        }
    return;
    }
