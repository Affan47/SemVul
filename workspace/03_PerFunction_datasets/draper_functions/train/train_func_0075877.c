print_fonts(poppler::document *doc)
{
    std::cout << "Document fonts:" << std::endl;
    std::vector<poppler::font_info> fl = doc->fonts();
    if (!fl.empty()) {
        std::vector<poppler::font_info>::const_iterator it = fl.begin(), it_end = fl.end();
        const std::ios_base::fmtflags f = std::cout.flags();
        std::left(std::cout);
        for (; it != it_end; ++it) {
            std::cout
                << " " << std::setw(out_width + 10) << it->name()
                << " " << std::setw(15) << out_font_info_type(it->type())
                << " " << std::setw(5) << it->is_embedded()
                << " " << std::setw(5) << it->is_subset()
                << " " << it->file()
                << std::endl;
        }
        std::cout.flags(f);
    } else {
        std::cout << "<no fonts>" << std::endl;
    }
    std::cout << std::endl;
}
