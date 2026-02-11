proc_to_s(self)
    VALUE self;
{
    struct BLOCK *data;
    NODE *node;
    char *cname = rb_obj_classname(self);
    const int w = (sizeof(VALUE) * CHAR_BIT) / 4;
    long len = strlen(cname)+6+w;
    VALUE str;

    Data_Get_Struct(self, struct BLOCK, data);
    if ((node = data->frame.node) || (node = data->body)) {
	len += strlen(node->nd_file) + 2 + (SIZEOF_LONG*CHAR_BIT-NODE_LSHIFT)/3;
	str = rb_str_new(0, len);
	snprintf(RSTRING(str)->ptr, len+1,
		 "#<%s:0x%.*lx@%s:%d>", cname, w, (VALUE)data->body,
		 node->nd_file, nd_line(node));
    }
    else {
	str = rb_str_new(0, len);
	snprintf(RSTRING(str)->ptr, len+1,
		 "#<%s:0x%.*lx>", cname, w, (VALUE)data->body);
    }
    RSTRING(str)->len = strlen(RSTRING(str)->ptr);
    if (OBJ_TAINTED(self)) OBJ_TAINT(str);

    return str;
}
