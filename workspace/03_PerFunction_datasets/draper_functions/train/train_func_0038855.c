createArrayClass(char *classname, Object *class_loader) {
    ClassBlock *elem_cb, *classblock;
    Class *class, *found = NULL;
    int len = strlen(classname);

    if((class = allocClass()) == NULL)
        return NULL;

    classblock = CLASS_CB(class);

    classblock->name = copyUtf8(classname);
    classblock->super = findSystemClass0(SYMBOL(java_lang_Object));
    classblock->method_table = CLASS_CB(classblock->super)->method_table;

    classblock->interfaces_count = 2;
    classblock->interfaces = sysMalloc(sizeof(Class*) * 2);
    classblock->interfaces[0] = findSystemClass0(SYMBOL(java_lang_Cloneable));
    classblock->interfaces[1] = findSystemClass0(SYMBOL(java_io_Serializable));

    classblock->state = CLASS_ARRAY;


    if(classname[1] == '[') {
        Class *comp_class =
                  findArrayClassFromClassLoader(classname + 1, class_loader);

        if(comp_class == NULL)
            goto error;

        classblock->element_class = CLASS_CB(comp_class)->element_class;
        classblock->dim = CLASS_CB(comp_class)->dim + 1;
    } else {
        if(classname[1] == 'L') {
            char element_name[len - 2];

            memcpy(element_name, classname + 2, len - 3);
            element_name[len - 3] = '\0';

            classblock->element_class =
                      findClassFromClassLoader(element_name, class_loader);
        } else
            classblock->element_class = findPrimitiveClass(classname[1]);

        if(classblock->element_class == NULL)
            goto error;

        classblock->dim = 1;
    }

    elem_cb = CLASS_CB(classblock->element_class);


    classblock->class_loader = elem_cb->class_loader;


    classblock->access_flags = (elem_cb->access_flags & ~ACC_INTERFACE) |
                               ACC_FINAL | ACC_ABSTRACT;

    prepareClass(class);

    if((found = addClassToHash(class, classblock->class_loader)) == class) {
        if(verbose)
            jam_printf("[Created array class %s]\n", classname);
        return class;
    }

error:
    classblock->flags = CLASS_CLASH;
    return found;
}
