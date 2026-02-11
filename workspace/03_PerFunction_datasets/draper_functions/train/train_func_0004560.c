ap_texpr0_array_is_template(ap_texpr0_t** texpr, size_t size, bool (*is_template)(ap_texpr0_t* texpr))
{
  size_t i;
  bool res = true;
  for (i=0; i<size; i++){
    res = is_template(texpr[i]);
    if (!res) break;
  }
  return res;
}
