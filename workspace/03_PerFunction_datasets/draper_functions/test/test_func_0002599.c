C4_Model_append_codegen(C4_Model *model,
                             gchar *global_code, gchar *local_code,
                             gchar *cflags_add){
    if((global_code) && (!C4_Model_string_list_contains(
                model->global_code_list, global_code)))
        g_ptr_array_add(model->global_code_list, g_strdup(global_code));
    if((local_code) && (!C4_Model_string_list_contains(
                model->local_code_list, local_code)))
        g_ptr_array_add(model->local_code_list, g_strdup(local_code));
    if((cflags_add) && (!C4_Model_string_list_contains(
                model->cflags_add_list, cflags_add)))
        g_ptr_array_add(model->cflags_add_list, g_strdup(cflags_add));
    return;
    }
