Rivet_BuildConfDictionary ( Tcl_Interp*           interp,
                                     rivet_server_conf*    rivet_conf)
{
    apr_table_t* conf_tables[3];
    Tcl_Obj*     keyval_list = NULL;
    Tcl_Obj*     key_list[2];
    int          it;
    Tcl_Obj*     conf_dict = Tcl_NewObj();

    static const char* section_names[] =
    {
        "dir",
        "user",
        "server"
    };

    enum
    {
        dir_conf_section,
        user_conf_section,
        server_conf_section
    };

    conf_tables[0] = rivet_conf->rivet_dir_vars;
    conf_tables[1] = rivet_conf->rivet_user_vars;
    conf_tables[2] = rivet_conf->rivet_server_vars;

    Tcl_IncrRefCount(conf_dict);

    for (it=0; it < 3; it++)
    {
        keyval_list = Rivet_ReadConfTable(interp,conf_tables[it]);

        if (keyval_list != NULL)
        {
            int       i;
            Tcl_Obj** objArrayPnt;
            int       objArrayCnt;
            Tcl_Obj*  val;

            key_list[0] = Tcl_NewStringObj(section_names[it],-1);
            Tcl_IncrRefCount(key_list[0]);

            Tcl_ListObjGetElements(interp,keyval_list,&objArrayCnt,&objArrayPnt);
            for (i=0; i < objArrayCnt; i+=2)
            {
                key_list[1] = objArrayPnt[i];
                val         = objArrayPnt[i+1];

                Tcl_IncrRefCount(key_list[1]);
                Tcl_IncrRefCount(val);

                Tcl_DictObjPutKeyList(interp,conf_dict,2,key_list,val);

                Tcl_DecrRefCount(key_list[1]);
                Tcl_DecrRefCount(val);
            }
            Tcl_DecrRefCount(key_list[0]);
            Tcl_DecrRefCount(keyval_list);
        }
        else
        {
            return NULL;
        }
    }

    return conf_dict;
}
