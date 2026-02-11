file_info_find(string_ty *server_side, int auto_alloc)
{
    file_info_ty    *fip;

    if (!file_info)
    {
	file_info = new symtab_ty(5);
	file_info->set_reap(file_info_reaper);
    }
    fip = (file_info_ty *)file_info->query(server_side);
    if (!fip && auto_alloc)
    {
	fip = file_info_new();
	file_info->assign(server_side, fip);
    }
    return fip;
}
