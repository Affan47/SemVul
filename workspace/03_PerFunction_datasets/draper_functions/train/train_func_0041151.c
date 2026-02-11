init(const std::string &app_root_dir)
{
    if (app_root_dir.empty()) res_dir = string(RES_DIR);
    else res_dir = app_root_dir + FS_SEPARATOR + string(RES_DIR);
}
