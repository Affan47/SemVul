Load(FILE *stream, ReadFunction readFn,void *arg)
{
    size_t i,len,keybuflen;
    HashTable *result=NULL,HT;
    char *keybuf=NULL,*valbuf=NULL;
    guid Guid;

    if (readFn == NULL) {
        readFn = DefaultLoadFunction;
        arg = &HT.ElementSize;
    }

    if (fread(&Guid,sizeof(guid),1,stream) == 0) {
        iError.RaiseError("iHashTable.Load",CONTAINER_ERROR_FILE_READ);
        return NULL;
    }
    if (memcmp(&Guid,&HashTableGuid,sizeof(guid))) {
        iError.RaiseError("iHashTable.Load",CONTAINER_ERROR_WRONGFILE);
        return NULL;
    }
    if (fread(&HT,1,sizeof(HashTable),stream) == 0) {
        iError.RaiseError("HashTable.Load",CONTAINER_ERROR_FILE_READ);
        return NULL;
    }
    result = iHashTable.Create(HT.ElementSize);
    if (result == NULL)
        return NULL;
    keybuflen = 4096;
    keybuf = malloc(keybuflen);
    valbuf = malloc(HT.ElementSize);
    result->Flags = HT.Flags;
    for (i=0; i< HT.count; i++) {
        if (decode_ule128(stream, &len) <= 0) {
        err:
            iError.RaiseError("iHashTable.Load",CONTAINER_ERROR_FILE_READ);
            goto out;
        }
        if (keybuflen < len) {
            void *tmp = realloc(keybuf,len);
            if (tmp == NULL) {
                iError.RaiseError("iHashTable.Load",CONTAINER_ERROR_NOMEMORY);
                goto out;
            }
            keybuf = tmp;
            keybuflen = len;
        }
        if (fread(keybuf,1,len,stream) == 0) {
            goto err;
        }
        if (readFn(valbuf,arg,stream) == 0) {
            goto err;
        }
        iHashTable.Add(result,keybuf,len,valbuf);
    }
out:
    if (keybuf) free(keybuf);
    if (valbuf) free(valbuf);
    return result;
}
