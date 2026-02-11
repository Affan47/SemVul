db_error(const char *s)
{
    if (s == NULL)
	s = "<NULL error message>";
    if (err_msg)
	db_free(err_msg);
    err_msg = db_store(s);
    err_flag = 1;
    if (auto_print_errors)
	db_print_error();
    err_code = DB_FAILED;
}
