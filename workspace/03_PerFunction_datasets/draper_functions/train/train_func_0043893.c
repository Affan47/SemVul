xml_getHead(const char *name, lList *list, lList *attributes) {
   lListElem *xml_head = NULL;

   xml_head = lCreateElem(XMLH_Type);

   if (xml_head) {

      lSetString(xml_head, XMLH_Version, "<?xml version='1.0'?>");
      lSetString(xml_head, XMLH_Name, name);
      lSetList(xml_head, XMLH_Attribute, attributes);
      lSetList(xml_head, XMLH_Element, list);
      xml_addAttribute(xml_head, "xmlns:xsd", "http://gridengine.sunsource.net/source/browse/*checkout*/gridengine/source/dist/util/resources/schemas/qstat/qstat.xsd?revision=1.11");


   }

   return xml_head;
}
