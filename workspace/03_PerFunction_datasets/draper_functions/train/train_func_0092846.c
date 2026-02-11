get_first_screen_number() const
{
    CYG_REPORT_FUNCNAMETYPE("CdlWizard::get_first_screen_number", "result %d");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();


    bool        result_set = false;
    cdl_int     result = -1;

    const std::vector<CdlProperty>& properties = get_properties();
    std::vector<CdlProperty>::const_iterator prop_i;
    for (prop_i = properties.begin(); prop_i != properties.end(); prop_i++) {
        if (CdlPropertyId_Screen != (*prop_i)->get_property_name()) {
            continue;
        }
        CdlProperty_TclCode tclprop = dynamic_cast<CdlProperty_TclCode>(*prop_i);
        cdl_int its_num = tclprop->get_number();
        if (!result_set || (its_num < result)) {
            result = its_num;
            result_set = true;
        }
    }

    CYG_REPORT_RETVAL((int) result);
    return result;
}
