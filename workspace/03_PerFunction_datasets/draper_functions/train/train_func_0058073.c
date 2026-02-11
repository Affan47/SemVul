findHashedClass(char *classname, Object *class_loader) {
    HashTable *table;
    Class *class;
    char *name;


    if((name = findUtf8(classname)) == NULL)
        return NULL;

    if(class_loader == NULL)
        table = &boot_classes;
    else
        if((table = classlibLoaderTable(class_loader)) == NULL)
            return NULL;

#undef HASH
#undef COMPARE
#define HASH(ptr) utf8Hash(ptr)
#define COMPARE(ptr1, ptr2, hash1, hash2) (hash1 == hash2) && \
            (ptr1 == CLASS_CB((Class *)ptr2)->name)


   findHashEntry((*table), name, class, FALSE, FALSE, TRUE);

   return class;
}
