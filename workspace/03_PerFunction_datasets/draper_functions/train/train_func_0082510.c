opal_class_initialize(opal_class_t *cls)
{
    opal_class_t *c;
    opal_construct_t* cls_construct_array;
    opal_destruct_t* cls_destruct_array;
    int cls_construct_array_count;
    int cls_destruct_array_count;
    int i;

    assert(cls);


    if (1 == cls->cls_initialized) {
        return;
    }
    opal_atomic_lock(&class_lock);


    if (1 == cls->cls_initialized) {
        opal_atomic_unlock(&class_lock);
        return;
    }


    cls->cls_depth = 0;
    cls_construct_array_count = 0;
    cls_destruct_array_count  = 0;
    for (c = cls; c; c = c->cls_parent) {
        if( NULL != c->cls_construct ) {
            cls_construct_array_count++;
        }
        if( NULL != c->cls_destruct ) {
            cls_destruct_array_count++;
        }
        cls->cls_depth++;
    }


    cls->cls_construct_array =
        (void (**)(opal_object_t*))malloc((cls_construct_array_count +
                                           cls_destruct_array_count + 2) *
                                          sizeof(opal_construct_t) );
    if (NULL == cls->cls_construct_array) {
        perror("Out of memory");
        exit(-1);
    }
    cls->cls_destruct_array =
        cls->cls_construct_array + cls_construct_array_count + 1;


    cls_construct_array = cls->cls_construct_array + cls_construct_array_count;
    cls_destruct_array  = cls->cls_destruct_array;

    c = cls;
    *cls_construct_array = NULL;
    for (i = 0; i < cls->cls_depth; i++) {
        if( NULL != c->cls_construct ) {
            --cls_construct_array;
            *cls_construct_array = c->cls_construct;
        }
        if( NULL != c->cls_destruct ) {
            *cls_destruct_array = c->cls_destruct;
            cls_destruct_array++;
        }
        c = c->cls_parent;
    }
    *cls_destruct_array = NULL;

    cls->cls_initialized = 1;
    save_class(cls);


    opal_atomic_unlock(&class_lock);
}
