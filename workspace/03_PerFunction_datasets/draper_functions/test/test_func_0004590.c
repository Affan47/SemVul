get_pa_object_entry(Pa_object *obj)
{
    int entry;
    Array_table *a;
    Var_table *v;
    Temp_table *t;
    Iv_table *i;
    Heap_table *h;
    Module_table *f, *s;

    switch(obj->kind) {
    case KIND_ARRAY :
        a = obj->tbl.a;
        entry = a->entry;
        break;
    case KIND_VAR :
        v = obj->tbl.v;
        entry = v->entry;
        break;
    case KIND_TEMP :
        t = obj->tbl.t;
        entry = t->entry;
        break;
    case KIND_INVISIBLE :
        i = obj->tbl.i;
        entry = i->entry;
        break;
    case KIND_HEAP :
        h = obj->tbl.h;
        entry = h->entry;
        break;
    case KIND_FUNC :
        f = obj->tbl.f;
        entry = f->entry;
        break;
    case KIND_SUB :
        s = obj->tbl.s;
        entry = s->entry;
        break;
    case KIND_UNINIT :
    case KIND_UNKNOWN :
    case KIND_FILE :
        entry = 0;
        break;
    default :
        entry = -1;
        fatal("unexpected kind\n");
        break;
    }

    return entry;
}
