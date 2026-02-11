construct_tex_name(const string &name, string &tex_name)
{

  tex_name = name;
  size_t pos = 0;
  while ((pos = tex_name.find('_', pos)) != string::npos)
    {
      tex_name.insert(pos, "\\");
      pos += 2;
    }
  return tex_name;
}
