result(const wxString& name, const wxString& project_url) {
    RESULT* pResult = NULL;

    try {
        if (!results.results.empty()) {

            for(unsigned int i=0; i< results.results.size();i++) {
                RESULT* tResult = results.results.at(i);
                wxString resname(tResult->name, wxConvUTF8);
                if(resname.IsSameAs(name)){
                    wxString resurl(tResult->project_url, wxConvUTF8);
                    if(resurl.IsSameAs(project_url)){
                        pResult = tResult;
                        break;
                    }
                }
            }
        }
    }
    catch (std::out_of_range e) {
        pResult = NULL;
    }

    return pResult;
}
