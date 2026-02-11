print_info(poppler::document *doc)
{
    std::cout << "Document information:" << std::endl;
    int major = 0, minor = 0;
    doc->get_pdf_version(&major, &minor);
    std::cout << std::setw(out_width) << "PDF version" << ": " << major << "." << minor << std::endl;
    std::string permanent_id, update_id;
    if (doc->get_pdf_id(&permanent_id, &update_id)) {
        std::cout << std::setw(out_width) << "PDF IDs" << ": P: " << permanent_id << " - U: " << update_id << std::endl;
    } else {
        std::cout << std::setw(out_width) << "PDF IDs" << ": <none>" << std::endl;
    }
    const std::vector<std::string> keys = doc->info_keys();
    std::vector<std::string>::const_iterator key_it = keys.begin(), key_end = keys.end();
    for (; key_it != key_end; ++key_it) {
        std::cout << std::setw(out_width) << *key_it << ": " << doc->info_key(*key_it) << std::endl;
    }
    std::cout << std::setw(out_width) << "Date (creation)" << ": " << out_date(doc->info_date("CreationDate")) << std::endl;
    std::cout << std::setw(out_width) << "Date (modification)" << ": " << out_date(doc->info_date("ModDate")) << std::endl;
    std::cout << std::setw(out_width) << "Number of pages" << ": " << doc->pages() << std::endl;
    std::cout << std::setw(out_width) << "Linearized" << ": " << doc->is_linearized() << std::endl;
    std::cout << std::setw(out_width) << "Encrypted" << ": " << doc->is_encrypted() << std::endl;
    std::cout << std::endl;
}
