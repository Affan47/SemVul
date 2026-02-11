proc_clone(self)
    VALUE self;
{
    struct BLOCK *orig, *data;
    VALUE bind;

    Data_Get_Struct(self, struct BLOCK, orig);
    bind = Data_Make_Struct(rb_obj_class(self),struct BLOCK,blk_mark,blk_free,data);
    CLONESETUP(bind, self);
    blk_dup(data, orig);

    return bind;
}
