checkClassAccess(Class *class1, Class *class2) {
    ClassBlock *cb1 = CLASS_CB(class1);


    if(cb1->access_flags & ACC_PUBLIC)
        return TRUE;

    if(classlibAccessCheck(class1, class2))
        return TRUE;


    return isSameRuntimePackage(class1, class2);
}
