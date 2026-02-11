parseShapeCircle(eGrid *grid, xmlNodePtr cur, float &x, float &y, float &radius, float& growth, const xmlChar * keyword)
{
    radius = myxmlGetPropFloat(cur, "radius");
    growth = myxmlGetPropFloat(cur, "growth");

    cur = cur->xmlChildrenNode;
    while( cur != NULL) {
        if (!xmlStrcmp(cur->name, (const xmlChar *)"text") || !xmlStrcmp(cur->name, (const xmlChar *)"comment")) {}
        else if (isElement(cur->name, (const xmlChar *)"Point", keyword)) {
            x = myxmlGetPropFloat(cur, "x");
            y = myxmlGetPropFloat(cur, "y");

            endElementAlternative(grid, cur, keyword);
            return true;
        }
        else if (isElement(cur->name, (const xmlChar *)"Alternative", keyword)) {
            if (isValidAlternative(cur, keyword)) {
                parseAlternativeContent(grid, cur);
            }
        }
        cur = cur->next;
    }
    return false;
}
