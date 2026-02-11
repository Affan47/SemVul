read_import_replacements(const char *old_module_name,
                         struct module_import *identifier)
{
    struct module_compatability *mcp;


    for (mcp = module_map_head; mcp; mcp = mcp->next) {
        if (!label_compare(mcp->old_module, old_module_name)) {

            if (
                   (mcp->tag_len == 0 &&
                    (mcp->tag == NULL ||
                     !label_compare(mcp->tag, identifier->label))) ||


                   (mcp->tag_len != 0 &&
                    !strncmp(mcp->tag, identifier->label, mcp->tag_len))
                ) {

                if (netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID,
				       NETSNMP_DS_LIB_MIB_WARNINGS)) {
                    snmp_log(LOG_WARNING,
                             "Importing %s from replacement module %s instead of %s (%s)\n",
                             identifier->label, mcp->new_module,
                             old_module_name, File);
		}
                (void) netsnmp_read_module(mcp->new_module);
                identifier->modid = which_module(mcp->new_module);
                return 1;
            }
        }
    }


    return read_module_replacements(old_module_name);
}
