Obj_drop(const void* thiz)
{
    Obj* o = (Obj*)thiz;
    if( --o->ref_cnt <= 0){
        if( o->destructor)
            (o->destructor(o));
    }
}
