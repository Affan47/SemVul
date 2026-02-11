create_top_links(const Links& links, const char *tag) {
    for (Links::const_iterator s = links.begin(); s != links.end(); ++s) {
        XML_Tag link(tag);
        add_link_attributes(link, detectLinkType(s->Target()), s->Target(), s->SourceLineno());
    }
}
