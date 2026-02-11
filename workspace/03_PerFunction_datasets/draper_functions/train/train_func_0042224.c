Jim_NewDictObj(Jim_Interp *interp, Jim_Obj *const *elements, int len)
{
    Jim_Obj *objPtr;
    int i;

    JimPanic((len % 2, "Jim_NewDictObj() 'len' argument must be even"));

    objPtr = Jim_NewObj(interp);
    objPtr->typePtr = &dictObjType;
    objPtr->bytes = NULL;
    objPtr->internalRep.ptr = Jim_Alloc(sizeof(Jim_HashTable));
    Jim_InitHashTable(objPtr->internalRep.ptr, &JimDictHashTableType, interp);
    for (i = 0; i < len; i += 2)
        DictAddElement(interp, objPtr, elements[i], elements[i + 1]);
    return objPtr;
}
