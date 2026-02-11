xmlrpc_struct_set_value_v(xmlrpc_env *   const envP,
                          xmlrpc_value * const strctP,
                          xmlrpc_value * const keyvalP,
                          xmlrpc_value * const valueP) {

    char *key;
    size_t key_len;
    int xmIndex;
    _struct_member *members, *member, new_member;
    xmlrpc_value *old_value;

    XMLRPC_ASSERT_ENV_OK(envP);
    XMLRPC_ASSERT_VALUE_OK(strctP);
    XMLRPC_ASSERT_VALUE_OK(keyvalP);
    XMLRPC_ASSERT_VALUE_OK(valueP);

    XMLRPC_TYPE_CHECK(envP, strctP, XMLRPC_TYPE_STRUCT);
    XMLRPC_TYPE_CHECK(envP, keyvalP, XMLRPC_TYPE_STRING);

    key = XMLRPC_MEMBLOCK_CONTENTS(char, &keyvalP->_block);
    key_len = XMLRPC_MEMBLOCK_SIZE(char, &keyvalP->_block) - 1;
    xmIndex = find_member(strctP, key, key_len);

    if (xmIndex >= 0) {


        members = XMLRPC_MEMBLOCK_CONTENTS(_struct_member, &strctP->_block);
        member = &members[xmIndex];


        old_value = member->value;
        member->value = valueP;
        xmlrpc_INCREF(member->value);
        xmlrpc_DECREF(old_value);
    } else {

        new_member.key_hash = get_hash(key, key_len);
        new_member.key      = keyvalP;
        new_member.value    = valueP;
        XMLRPC_MEMBLOCK_APPEND(_struct_member, envP, &strctP->_block,
                               &new_member, 1);
        XMLRPC_FAIL_IF_FAULT(envP);
        xmlrpc_INCREF(keyvalP);
        xmlrpc_INCREF(valueP);
    }

cleanup:
    return;
}
