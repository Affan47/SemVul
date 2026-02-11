Analysis_decide_scan_query(FastaDB *query_fdb,
                                           FastaDB *target_fdb,
                                           gchar *force_scan){
    register CompoundFile_Pos query_size, target_size;
    if(!g_strcasecmp(force_scan, "none")){
        query_size = CompoundFile_get_length(query_fdb->cf);
        target_size = CompoundFile_get_length(target_fdb->cf);
        if((query_size >> 4) < target_size)
            return FALSE;
        else
            return TRUE;
    } else if((!g_strcasecmp(force_scan, "query"))
           || (!g_strcasecmp(force_scan, "q"))){
        return TRUE;
    } else if((!g_strcasecmp(force_scan, "target"))
           || (!g_strcasecmp(force_scan, "t"))){
        return FALSE;
    } else {
        g_error("Unknown force_scan command [%s]", force_scan);
        }
    return FALSE;
    }
