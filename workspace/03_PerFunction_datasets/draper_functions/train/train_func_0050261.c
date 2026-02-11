php_sqlite3_compare_stmt_zval_free( php_sqlite3_free_list **free_list, zval *statement )
{
	return ((*free_list)->stmt_obj->initialised && statement == (*free_list)->stmt_obj_zval);
}
