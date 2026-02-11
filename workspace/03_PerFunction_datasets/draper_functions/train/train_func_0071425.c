free_xml(xmlNode * child)
{
    if (child != NULL) {
        xmlNode *top = NULL;
        xmlDoc *doc = child->doc;

        if (doc != NULL) {
            top = xmlDocGetRootElement(doc);
        }

        if (doc != NULL && top == child) {

            xmlFreeDoc(doc);

        } else {


            xmlUnlinkNode(child);
            xmlFreeNode(child);
        }
    }
}
