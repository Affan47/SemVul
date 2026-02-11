objectToPropertyNode(StoreState &state, QObject *o)
{
    Node pnode;

    DEBUG << "objectToPropertyNode: " << o << endl;

    if (state.map.contains(o) && state.map.value(o) != Node()) {
        pnode = state.map.value(o);
    } else {


        Uri uri = getUriFrom(o);
        if (uri != Uri()) {
            pnode = Node(uri);
            return pnode;
        }
    }

    return pnode;
}
