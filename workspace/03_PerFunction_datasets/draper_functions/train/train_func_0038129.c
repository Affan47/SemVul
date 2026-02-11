_cpp_destroy_iconv (cpp_reader *pfile)
{
  if (HAVE_ICONV)
    {
      if (pfile->narrow_cset_desc.func == convert_using_iconv)
	iconv_close (pfile->narrow_cset_desc.cd);
      if (pfile->wide_cset_desc.func == convert_using_iconv)
	iconv_close (pfile->wide_cset_desc.cd);
    }
}
