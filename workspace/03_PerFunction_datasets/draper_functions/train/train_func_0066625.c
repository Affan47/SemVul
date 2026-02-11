Get_Path_Name(WamWord path_name_word)
{
  char *path_name;

  path_name = Rd_String_Check(path_name_word);
  if ((path_name = M_Absolute_Path_Name(path_name)) == NULL)
    Pl_Err_Domain(domain_os_path, path_name_word);

  return path_name;
}
