gp_file_name_is_parent(const char *fname, uint len)
{   return len == 2 && fname[0] == '.' && fname[1] == '.';
}
