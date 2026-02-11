create_codecvt(std::locale const &in,std::string const &encoding,character_facet_type type)
    {
        std::auto_ptr<util::base_converter> cvt;
        if(conv::impl::normalize_encoding(encoding.c_str())=="utf8")
            cvt = util::create_utf8_converter();
        else {
            cvt = util::create_simple_converter(encoding);
            if(!cvt.get()) {
                try {
                    cvt = create_uconv_converter(encoding);
                }
                catch(std::exception const &)
                {

                }
            }
        }
        return util::create_codecvt(in,cvt,type);
    }

}
