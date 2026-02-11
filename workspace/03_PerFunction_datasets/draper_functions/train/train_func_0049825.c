ACL_AttrGetterFirst(ACLAttrGetterList_t *getters)
{
    ACLAttrGetter_t * first = 0;

    if (getters && *getters) {

        first = (ACLAttrGetter_t *)(*getters);
    }

    return first;
}
