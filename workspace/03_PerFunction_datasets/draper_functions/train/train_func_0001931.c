set_file_aliases(const DjVuFile * file)
{
   DEBUG_MSG("DjVuDocument::set_file_aliases(): setting global aliases for file '"
	     << file->get_url() << "'\n");
   DEBUG_MAKE_INDENT(3);

   DjVuPortcaster * pcaster=DjVuPort::get_portcaster();

   GMonitorLock lock(&((DjVuFile *) file)->get_safe_flags());
   pcaster->clear_aliases(file);
   if (file->is_decode_ok() && cache)
   {


      pcaster->add_alias(file, file->get_url().get_string());
      if (flags & (DOC_NDIR_KNOWN | DOC_DIR_KNOWN))
      {
	 int page_num=url_to_page(file->get_url());
	 if (page_num>=0)
	 {
	    if (page_num==0) pcaster->add_alias(file, init_url.get_string()+"#-1");
	    pcaster->add_alias(file, init_url.get_string()+"#"+GUTF8String(page_num));
	 }
      }


      pcaster->add_alias(file, file->get_url().get_string()+"#-1");
   } else pcaster->add_alias(file, get_int_prefix()+file->get_url());
}
