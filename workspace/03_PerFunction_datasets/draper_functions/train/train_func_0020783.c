PKIX_PL_Object_ToString(
        PKIX_PL_Object *object,
        PKIX_PL_String **pString,
        void *plContext)
{
        PKIX_PL_Object *objectHeader = NULL;
        PKIX_PL_ToStringCallback func = NULL;
        pkix_ClassTable_Entry entry;
        PKIX_PL_String *objectString = NULL;

        PKIX_ENTER(OBJECT, "PKIX_PL_Object_ToString");
        PKIX_NULLCHECK_TWO(object, pString);


        PKIX_CHECK(pkix_pl_Object_GetHeader(object, &objectHeader, plContext),
                    PKIX_RECEIVEDCORRUPTEDOBJECTARGUMENT);


        if (!objectHeader->stringRep){

                PKIX_UInt32 objType = objectHeader->type;

                if (objType >= PKIX_NUMTYPES){
#ifdef PKIX_USER_OBJECT_TYPE
                        pkix_ClassTable_Entry *ctEntry = NULL;

                        PKIX_OBJECT_DEBUG("\tCalling PR_Lock).\n");
                        PR_Lock(classTableLock);
                        pkixErrorResult = pkix_pl_PrimHashTable_Lookup
                                (classTable,
                                (void *)&objType,
                                objType,
                                NULL,
                                (void **)&ctEntry,
                                plContext);
                        PKIX_OBJECT_DEBUG("\tCalling PR_Unlock).\n");
                        PR_Unlock(classTableLock);
                        if (pkixErrorResult){
                                PKIX_ERROR_FATAL
                                        (PKIX_ERRORGETTINGCLASSTABLEENTRY);
                        }

                        if ((ctEntry == NULL) ||
                            (ctEntry->toStringFunction == NULL)) {
                                PKIX_ERROR_FATAL(PKIX_UNDEFINEDCALLBACK);
                        }

                        func = ctEntry->toStringFunction;
#else
                        PORT_Assert (0);
                        pkixErrorCode = PKIX_UNKNOWNOBJECTTYPE;
                        pkixErrorClass = PKIX_FATAL_ERROR;
                        goto cleanup;
#endif
                } else {
                        entry = systemClasses[objType];
                        func = entry.toStringFunction;
                        if (func == NULL){
                                func = pkix_pl_Object_ToString_Default;
                        }
                }

                PKIX_CHECK(func(object, &objectString, plContext),
                            PKIX_OBJECTSPECIFICFUNCTIONFAILED);

                if (!objectHeader->stringRep){

                        PKIX_CHECK(pkix_LockObject(object, plContext),
                                    PKIX_ERRORLOCKINGOBJECT);

                        if (!objectHeader->stringRep){

                                objectHeader->stringRep = objectString;
                                objectString = NULL;
                        }

                        PKIX_CHECK(pkix_UnlockObject(object, plContext),
                                    PKIX_ERRORUNLOCKINGOBJECT);
                }
        }


        *pString = objectHeader->stringRep;
        objectHeader->stringRep = NULL;

cleanup:
        if (objectHeader) {
            PKIX_DECREF(objectHeader->stringRep);
        }
        PKIX_DECREF(objectString);

        PKIX_RETURN(OBJECT);
}
