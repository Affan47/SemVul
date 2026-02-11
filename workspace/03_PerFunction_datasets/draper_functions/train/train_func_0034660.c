parseObstacleWall(eGrid *grid, xmlNodePtr cur, const xmlChar * keyword)
{
    ePoint *R = NULL;
    REAL x, y;

    REAL height = myxmlGetPropFloat(cur, "height");
    cur = cur->xmlChildrenNode;

    while (cur != NULL) {
        if (!xmlStrcmp(cur->name, (const xmlChar *)"text") || !xmlStrcmp(cur->name, (const xmlChar *)"comment")) {}
        else if (isElement(cur->name, (const xmlChar *)"Point", keyword)) {
            x = myxmlGetPropFloat(cur, "x");
            y = myxmlGetPropFloat(cur, "y");

            if (R == NULL)
                R = grid->Insert(eCoord(x, y) * sizeMultiplier);
            else
                R = this->DrawRim(grid, R, eCoord(x, y) * sizeMultiplier, height );
            endElementAlternative(grid, cur, keyword);
        }
        else if (isElement(cur->name, (const xmlChar *)"Alternative", keyword)) {
            if (isValidAlternative(cur, keyword)) {
                parseAlternativeContent(grid, cur);
            }
        }
        cur = cur->next;
    }
    sg_Deprecated();
}
