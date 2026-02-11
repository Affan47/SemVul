moveItemTo(Item item, int x, int y) {
    Window parent_return=0,
        root_return=0,
        *children_return = NULL;

    unsigned int nchildren_return;


    if (!XQueryTree(display(), window(),
                    &root_return, &parent_return, &children_return, &nchildren_return))
        parent_return = parent_return;

    if (children_return != NULL)
        XFree(children_return);

    int dest_x = 0, dest_y = 0;
    Window itemwin = 0;
    if (!XTranslateCoordinates(display(),
                               root_return, window(),
                               x, y, &dest_x, &dest_y,
                               &itemwin))
        return false;

    ItemList::iterator it = find_if(begin(), end(),
                                    CompareWindow(&FbWindow::window,
                                                  itemwin));

    if (it == end())
        return false;

    Window child_return = 0;

    if (!XTranslateCoordinates(display(),
                               window(), itemwin,
                               dest_x, dest_y, &x, &y,
                               &child_return))
        return false;
    return true;
}
