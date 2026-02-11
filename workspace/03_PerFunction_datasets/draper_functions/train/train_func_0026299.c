convert_params(xmlrpc_env *env, unsigned *depth, xml_element *elem)
{
    xmlrpc_value *array, *item;
    size_t size, i;
    xml_element **params, *param, *value;

    XMLRPC_ASSERT_ENV_OK(env);
    XMLRPC_ASSERT(elem != NULL);


    item = NULL;


    array = xmlrpc_build_value(env, "()");
    XMLRPC_FAIL_IF_FAULT(env);


    CHECK_NAME(env, elem, "params");


    size = xml_element_children_size(elem);
    params = xml_element_children(elem);
    for (i = 0; i < size; i++) {
        param = params[i];
        CHECK_NAME(env, param, "param");
        CHECK_CHILD_COUNT(env, param, 1);

        value = xml_element_children(param)[0];
        item = convert_value(env, depth, value);
        XMLRPC_FAIL_IF_FAULT(env);

        xmlrpc_array_append_item(env, array, item);
        xmlrpc_DECREF(item);
        item = NULL;
        XMLRPC_FAIL_IF_FAULT(env);
    }

 cleanup:
    if (env->fault_occurred) {
        if (array)
            xmlrpc_DECREF(array);
        if (item)
            xmlrpc_DECREF(item);
        return NULL;
    }
    return array;
}
