create_codecvt( std::locale const &in,
                                std::string const &locale_name,
                                character_facet_type type,
                                utf8_support utf)
    {
        if(utf == utf8_from_wide) {
            return util::create_codecvt(in,util::create_utf8_converter(),type);
        }
        switch(type) {
        case char_facet:
            return codecvt_bychar<char>(in,locale_name);
        case wchar_t_facet:
            return codecvt_bychar<wchar_t>(in,locale_name);
        #if defined(BOOST_HAS_CHAR16_T) && !defined(BOOST_NO_CHAR16_T_CODECVT)
        case char16_t_facet:
            return codecvt_bychar<char16_t>(in,locale_name);
        #endif
        #if defined(BOOST_HAS_CHAR32_T) && !defined(BOOST_NO_CHAR32_T_CODECVT)
        case char32_t_facet:
            return codecvt_bychar<char32_t>(in,locale_name);
        #endif
        default:
            return in;
        }
    }
