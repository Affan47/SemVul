findMethodHandleInvoker(Class *class,
                                                Class *accessing_class,
                                                char *methodname, char *type) {

    Object *name_str = findInternedString(createString(methodname));
    Class *obj_array_class = findArrayClass("[Ljava/lang/Object;");
    PolyMethodBlock *pmb;
    Object *appendix_box;
    Object *member_name;
    Object *method_type;

    if(name_str == NULL || obj_array_class == NULL)
        return NULL;

    appendix_box = allocArray(obj_array_class, 1, sizeof(Object*));
    if(appendix_box == NULL)
        return NULL;

    method_type = findMethodHandleType(type, accessing_class);
    if(method_type == NULL)
        return NULL;

    member_name = *(Object**)executeStaticMethod(MHN_linkMethod_mb->class,
                                                 MHN_linkMethod_mb,
                                                 accessing_class,
                                                 REF_invokeVirtual,
                                                 class,
                                                 name_str,
                                                 method_type,
                                                 appendix_box);

    if(exceptionOccurred())
        return NULL;

    pmb = sysMalloc(sizeof(PolyMethodBlock));
    pmb->appendix = ARRAY_DATA(appendix_box, Object*)[0];
    pmb->mb = INST_DATA(member_name, MethodBlock*, mem_name_vmtarget_offset);

    return pmb;
}
