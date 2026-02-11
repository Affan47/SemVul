php_get_wrapper_errors_list(php_stream_wrapper *wrapper TSRMLS_DC)
{
    zend_llist *list = NULL;
    if (!FG(wrapper_errors)) {
        return NULL;
    } else {
        zend_hash_find(FG(wrapper_errors), (const char*)&wrapper,
            sizeof wrapper, (void**)&list);
        return list;
    }
}
