xml_addStylesheet(lListElem *xml_head, const char* name, const char *url, const char *version) {
   lListElem *stylesheet_elem = lCreateElem(XMLS_Type);
   lList *stylesheet_list = NULL;

   if (stylesheet_elem) {
      lSetString(stylesheet_elem, XMLS_Name, name);
      lSetString(stylesheet_elem, XMLS_Value, url);
      lSetString(stylesheet_elem, XMLS_Version, version);
      stylesheet_list = lGetList(xml_head, XMLH_Stylesheet);
      if (!stylesheet_list)
         lSetList(xml_head, XMLH_Stylesheet, (stylesheet_list = lCreateList("Stylesheet", XMLS_Type)));

      lAppendElem(stylesheet_list, stylesheet_elem);
   }
}
