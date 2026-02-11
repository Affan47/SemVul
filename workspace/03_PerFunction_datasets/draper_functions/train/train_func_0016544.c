pick(const struct atmsvc_msg *msg,int field)
{
    VALUE out;

    if (msg->type >= MSG_TYPES) {
	fprintf(stderr,"invalid message type %d",msg->type);
	exit(1);
    }
    if (!(types[msg->type].fields & field)) yyerror("no such field in message");
    out.type = type_of(field);
#define _COPY(V,M) V = M
COPY_MSG_VAL(out)
#undef _COPY
    return out;
}
