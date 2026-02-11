Typemaker2_TypeManager_MakeTypeDerivatives(TYPEMAKER2_TYPEMANAGER *tym,
					       TYPEMAKER2_TYPE *ty,
					       const char *baseType,
					       const char *nType, const char *nPrefix) {
  TYPEMAKER2_TYPE *t2;
  char tbuf[256];
  int rv;

  t2=Typemaker2_Type_new();
  Typemaker2_Type_SetExtends(t2, baseType);
  Typemaker2_Type_SetType(t2, TypeMaker2_Type_Pointer);
  Typemaker2_Type_SetBaseType(t2, Typemaker2_Type_GetName(ty));

  snprintf(tbuf, sizeof(tbuf)-1, "%s_%s", Typemaker2_Type_GetName(ty), nType);
  tbuf[sizeof(tbuf)-1]=0;
  Typemaker2_Type_SetName(t2, tbuf);

  snprintf(tbuf, sizeof(tbuf)-1, "%s_%s", Typemaker2_Type_GetIdentifier(ty), nType);
  tbuf[sizeof(tbuf)-1]=0;
  Typemaker2_Type_SetIdentifier(t2, tbuf);

  snprintf(tbuf, sizeof(tbuf)-1, "%s_%s", Typemaker2_Type_GetPrefix(ty), nPrefix);
  tbuf[sizeof(tbuf)-1]=0;
  Typemaker2_Type_SetPrefix(t2, tbuf);

  Typemaker2_TypeManager_AddType(tym, t2);


  rv=Typemaker2_TypeManager_SetTypePtrs(tym, t2);
  if (rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
    return rv;
  }
  rv=Typemaker2_TypeManager_SetMemberTypePtrs(tym, t2);
  if (rv<0) {
    DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
    return rv;
  }

  return 0;
}
