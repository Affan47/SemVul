pkix_pl_LdapDefaultClient_MakeAndFilter(
        PLArenaPool *arena,
        LDAPNameComponent **nameComponents,
        LDAPFilter **pFilter,
        void *plContext)
{
        LDAPFilter **setOfFilter;
        LDAPFilter *andFilter = NULL;
        LDAPFilter *currentFilter = NULL;
        PKIX_UInt32 componentsPresent = 0;
        void *v = NULL;
        unsigned char *component = NULL;
        LDAPNameComponent **componentP = NULL;

        PKIX_ENTER(CERTSTORE, "pkix_pl_LdapDefaultClient_MakeAndFilter");
        PKIX_NULLCHECK_THREE(arena, nameComponents, pFilter);


        for (componentP = nameComponents, componentsPresent = 0;
                *(componentP++) != NULL;
                componentsPresent++) {}


        PKIX_PL_NSSCALLRV(CERTSTORE, v, PORT_ArenaZAlloc,
                (arena, (componentsPresent + 1)*sizeof(LDAPFilter *)));
        setOfFilter = (LDAPFilter **)v;


        PKIX_PL_NSSCALLRV(CERTSTORE, v, PORT_ArenaZNewArray,
                (arena, LDAPFilter, componentsPresent + 1));
        setOfFilter[0] = (LDAPFilter *)v;


        andFilter = setOfFilter[0];


        andFilter->selector = LDAP_ANDFILTER_TYPE;
        andFilter->filter.andFilter.filters = setOfFilter;

        currentFilter = andFilter + 1;

        for (componentP = nameComponents, componentsPresent = 0;
                *(componentP) != NULL; componentP++) {
                setOfFilter[componentsPresent++] = currentFilter;
                currentFilter->selector = LDAP_EQUALFILTER_TYPE;
                component = (*componentP)->attrType;
                currentFilter->filter.equalFilter.attrType.data = component;
                currentFilter->filter.equalFilter.attrType.len =
                        PL_strlen((const char *)component);
                component = (*componentP)->attrValue;
                currentFilter->filter.equalFilter.attrValue.data = component;
                currentFilter->filter.equalFilter.attrValue.len =
                        PL_strlen((const char *)component);
                currentFilter++;
        }

        setOfFilter[componentsPresent] = NULL;

        *pFilter = andFilter;

        PKIX_RETURN(CERTSTORE);

}
