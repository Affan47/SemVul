NewSetterFilter (
    Obj                 getter )
{
    Obj                 setter;

    setter = NewOperation( StringFilterSetter, 2, ArglistObjVal,
                           DoSetFilter );
    FLAG1_FILT(setter)  = FLAG1_FILT(getter);
    FLAG2_FILT(setter)  = INTOBJ_INT( 0 );
    CHANGED_BAG(setter);

    return setter;
}
