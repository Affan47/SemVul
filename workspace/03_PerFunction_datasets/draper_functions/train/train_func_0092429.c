get_view(unsigned int handle, const void **viewp)
{
  off_t offset;
  size_t filesize;
  Input_file *input_file;
  if (this->in_claim_file_handler_)
    {

      const struct ld_plugin_input_file &f = this->plugin_input_file_;
      offset = f.offset;
      filesize = f.filesize;
      input_file = this->input_file_;
    }
  else
    {

      if (this->object(handle) == NULL)
        return LDPS_BAD_HANDLE;
      Pluginobj* obj = this->object(handle)->pluginobj();
      if (obj == NULL)
        return LDPS_BAD_HANDLE;
      offset = obj->offset();
      filesize = obj->filesize();
      input_file = obj->input_file();
    }
  *viewp = (void*) input_file->file().get_view(offset, 0, filesize, false,
                                               false);
  return LDPS_OK;
}
