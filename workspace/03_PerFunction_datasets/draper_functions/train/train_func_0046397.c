delete_item( TemporaryItem * tempitem )
{

    bool in_list = false;
    for ( std::list<TemporaryItem*>::iterator it = itemlist.begin(); it != itemlist.end(); ++it ) {
        if ( *it == tempitem ) {
            in_list = true;
            break;
        }
    }
    if (in_list) {
        itemlist.remove(tempitem);
        delete tempitem;
    }
}
