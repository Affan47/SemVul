enumerateProperties(as_object& obj)
{


    std::set<as_object*> visited;

    SortedPropertyList to;
    PropertyEnumerator e(to);
    as_object* current(&obj);

    while (current && visited.insert(current).second) {
        current->visitProperties<IsEnumerable>(e);
        current = current->get_prototype();
    }
    return to;

}
