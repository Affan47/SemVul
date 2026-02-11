iterator_find(const PropertyList::container& p, const ObjectURI& uri, VM& vm)
{
    const bool caseless = vm.getSWFVersion() < 7;

    if (!caseless) {
        return p.project<PropertyList::CreationOrder>(
                p.get<PropertyList::Case>().find(uri));
    }

    return p.project<PropertyList::CreationOrder>(
            p.get<PropertyList::NoCase>().find(uri));
}

}
