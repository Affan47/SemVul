want_this_port(char **include_list, char **exclude_list,
                           ompi_common_verbs_device_item_t *di, int port)
{
    int i;
    char name[1024];


    if (NULL == include_list && NULL == exclude_list) {
        return true;
    }


    if (NULL != include_list) {
        for (i = 0; NULL != include_list[i]; ++i) {

            if (strcmp(di->device_name, include_list[i]) == 0) {
                return true;
            }


            snprintf(name, sizeof(name), "%s:%d", di->device_name, port);
            if (strcmp(name, include_list[i]) == 0) {
                return true;
            }
        }


        return false;
    }


    else {
        for (i = 0; NULL != exclude_list[i]; ++i) {

            if (strcmp(di->device_name, exclude_list[i]) == 0) {
                return false;
            }


            snprintf(name, sizeof(name), "%s:%d", di->device_name, port);
            if (strcmp(name, exclude_list[i]) == 0) {
                return false;
            }
        }


        return true;
    }


}
