CheckForAutoVersioning()
{

    m_bAutoVersioning = false;
    m_sAutoVersion = wxEmptyString;
    m_sVersionHeader = wxEmptyString;
    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
    TiXmlNode *node, *child;
    if(project){
        node = project->GetExtensionsNode();
        child = 0;
        while((child = node->IterateChildren(child))){
            wxString sNodeValue = wxString(child->Value(), wxConvUTF8);
            if(sNodeValue.Cmp(wxT("AutoVersioning")) == 0){
                m_bAutoVersioning = true;

                TiXmlHandle Handle(child);
                if(const TiXmlElement* pElem = Handle.FirstChildElement("Settings").ToElement()){
                    m_sVersionHeader = wxString(pElem->Attribute("header_path"), wxConvUTF8);
                }
                else{
                    AppendToLog(_("Unable to get the AutoVersion header path."), LOG_ERROR);
                }
                break;
            }
        }
    }
}
