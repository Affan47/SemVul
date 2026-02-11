DoSampleCode(HighlightLanguage language, TiXmlElement* node)
{
    TiXmlElement* sample = node->FirstChildElement("SampleCode");
    if (!sample)
        return;
    wxString code = wxString ( sample->Attribute("value"), wxConvUTF8 );
    if (code.IsEmpty())
        return;
    int breakLine = sample->Attribute("breakpoint_line") ? atol(sample->Attribute("breakpoint_line")) : -1;
    int debugLine = sample->Attribute("debug_line") ? atol(sample->Attribute("debug_line")) : -1;
    int errorLine = sample->Attribute("error_line") ? atol(sample->Attribute("error_line")) : -1;
    m_pTarget->SetSampleCode(language, code, breakLine, debugLine, errorLine);
}
