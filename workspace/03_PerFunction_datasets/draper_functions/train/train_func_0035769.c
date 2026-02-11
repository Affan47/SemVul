lg_FindPrivateKeyAttribute(LGObjectCache *obj, CK_ATTRIBUTE_TYPE type,
				CK_ATTRIBUTE *attribute)
{
    NSSLOWKEYPrivateKey  *key;
    char *label;
    CK_RV crv;

    switch (type) {
    case CKA_PRIVATE:
    case CKA_SENSITIVE:
    case CKA_ALWAYS_SENSITIVE:
    case CKA_EXTRACTABLE:
    case CKA_MODIFIABLE:
    case CKA_LOCAL:
	return LG_CLONE_ATTR(attribute,type,lg_StaticTrueAttr);
    case CKA_NEVER_EXTRACTABLE:
	return LG_CLONE_ATTR(attribute,type,lg_StaticFalseAttr);
    case CKA_SUBJECT:
	   return LG_CLONE_ATTR(attribute,type,lg_StaticNullAttr);
    case CKA_START_DATE:
    case CKA_END_DATE:
	   return LG_CLONE_ATTR(attribute,type,lg_StaticNullAttr);
    case CKA_LABEL:
        label = lg_FindKeyNicknameByPublicKey(obj->sdb, &obj->dbKey);
	if (label == NULL) {
	   return LG_CLONE_ATTR(attribute,type,lg_StaticNullAttr);
	}
	crv = lg_CopyAttribute(attribute,type,label,PORT_Strlen(label));
	PORT_Free(label);
	return crv;
    default:
	break;
    }
    key = lg_GetPrivateKey(obj);
    if (key == NULL) {
	return CKR_OBJECT_HANDLE_INVALID;
    }
    switch (key->keyType) {
    case NSSLOWKEYRSAKey:
	return lg_FindRSAPrivateKeyAttribute(key,type,attribute,obj->sdb);
    case NSSLOWKEYDSAKey:
	return lg_FindDSAPrivateKeyAttribute(key,type,attribute,obj->sdb);
    case NSSLOWKEYDHKey:
	return lg_FindDHPrivateKeyAttribute(key,type,attribute,obj->sdb);
#ifdef NSS_ENABLE_ECC
    case NSSLOWKEYECKey:
	return lg_FindECPrivateKeyAttribute(key,type,attribute,obj->sdb);
#endif
    default:
	break;
    }

    return lg_invalidAttribute(attribute);
}
