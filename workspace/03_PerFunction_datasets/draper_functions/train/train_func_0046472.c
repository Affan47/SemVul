create_parsing( std::locale const &in,
                            boost::shared_ptr<locale_t> lc,
                            character_facet_type type)
{
        switch(type) {
        case char_facet:
            return create_parsing_impl<char>(in,lc);
        case wchar_t_facet:
            return create_parsing_impl<wchar_t>(in,lc);
        default:
            return in;
        }
}
