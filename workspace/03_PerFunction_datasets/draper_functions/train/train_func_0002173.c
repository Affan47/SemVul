begin(const std::string &src_chset,
			   const std::string &dst_chset)
{
	end();

	if ((handle=libmail_u_convert_init(src_chset.c_str(),
					   dst_chset.c_str(),
					   &iconv_trampoline,
					   this)) == NULL)
		return false;
	return true;
}
