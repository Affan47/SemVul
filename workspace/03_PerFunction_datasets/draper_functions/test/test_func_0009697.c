fwbExternalEntityLoader(const char *URL,
                                          const char *ID,
                                          xmlParserCtxtPtr ctxt)
{
    xmlParserInputPtr ret;

#ifdef FW_XMLTOOLS_VERBOSE
    cerr << "ENTITY: " << URL << " " << string((ID)?ID:"(null)") << endl;
#endif

    string fname;

    fname=string(current_template_dir) + FS_SEPARATOR;

    string url=URL;
    string::size_type pos=url.find_last_of("/\\");
    fname+=(pos==string::npos)?url:url.substr(pos+1);

#ifdef FW_XMLTOOLS_VERBOSE
    cerr << "ENTITY FNAME: " << fname << endl;
#endif
    ret = xmlNewInputFromFile(ctxt, fname.c_str());
    if(ret)
        return(ret);
    else if(XMLTools::defaultLoader)
        return XMLTools::defaultLoader(URL, ID, ctxt);
    else
        return NULL;
}
