get_properties(std::string id, std::vector<CdlProperty>& result) const
{
    CYG_REPORT_FUNCNAME("CdlNode::get_properties");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();

    std::vector<CdlProperty>::const_iterator prop_i;
    for (prop_i = properties.begin(); prop_i != properties.end(); prop_i++) {
        if ((*prop_i)->get_property_name() == id) {
            result.push_back(*prop_i);
        }
    }

    CYG_REPORT_RETURN();
}
