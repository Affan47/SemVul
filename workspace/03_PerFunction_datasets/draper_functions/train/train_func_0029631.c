usdlg_data_destroy(struct usdata_hash *ushash)
{
  usdata_hash_data_iterate(ushash, data) {
    usdata_destroy(data);
  } usdata_hash_data_iterate_end;
  usdata_hash_destroy(ushash);
}
