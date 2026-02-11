FindWindowRecursively(const wxWindow* parent, const wxWindow* handle)

{
    if ( parent )
    {

        if ( parent == handle )
            return (wxWindow *)parent;


        for ( wxWindowList::compatibility_iterator node = parent->GetChildren().GetFirst();
              node;
              node = node->GetNext() )
        {

            wxWindow *win = (wxWindow *)node->GetData();
            wxWindow *retwin = FindWindowRecursively(win, handle);
            if (retwin)
                return retwin;
        }
    }


    return NULL;
}
