get_screen(cdl_int screen) const
{
    CYG_REPORT_FUNCNAME("CdlWizard::get_screen");
    CYG_REPORT_FUNCARG2XV(this, (int)screen);
    CYG_PRECONDITION_THISC();

    static cdl_tcl_code null_result     = "";
    cdl_tcl_code&       result          = null_result;

    const std::vector<CdlProperty>& properties = get_properties();
    std::vector<CdlProperty>::const_iterator prop_i;
    for (prop_i = properties.begin(); prop_i != properties.end(); prop_i++) {
        if (CdlPropertyId_Screen != (*prop_i)->get_property_name()) {
            continue;
        }
        CdlProperty_TclCode tclprop = dynamic_cast<CdlProperty_TclCode>(*prop_i);
        if (tclprop->get_number() == screen) {
            result     = tclprop->get_code();
            break;
        }
    }

    CYG_REPORT_RETURN();
    return result;
}

