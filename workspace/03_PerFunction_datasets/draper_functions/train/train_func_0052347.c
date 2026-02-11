read_uvector(ScmPort *port, const char *tag,
                           ScmReadContext *ctx)
{
    ScmChar c;
    ScmObj list, uv = SCM_UNDEFINED;

    SCM_GETC(c, port);
    if (c != '(') Scm_Error("bad uniform vector syntax for %s", tag);
    list = Scm_ReadList(SCM_OBJ(port), ')');
    if (strcmp(tag, "s8") == 0)  uv = Scm_ListToS8Vector(list, 0);
    else if (strcmp(tag, "u8") == 0)  uv = Scm_ListToU8Vector(list, 0);
    else if (strcmp(tag, "s16") == 0) uv = Scm_ListToS16Vector(list, 0);
    else if (strcmp(tag, "u16") == 0) uv = Scm_ListToU16Vector(list, 0);
    else if (strcmp(tag, "s32") == 0) uv = Scm_ListToS32Vector(list, 0);
    else if (strcmp(tag, "u32") == 0) uv = Scm_ListToU32Vector(list, 0);
    else if (strcmp(tag, "s64") == 0) uv = Scm_ListToS64Vector(list, 0);
    else if (strcmp(tag, "u64") == 0) uv = Scm_ListToU64Vector(list, 0);
    else if (strcmp(tag, "f16") == 0) uv = Scm_ListToF16Vector(list, 0);
    else if (strcmp(tag, "f32") == 0) uv = Scm_ListToF32Vector(list, 0);
    else if (strcmp(tag, "f64") == 0) uv = Scm_ListToF64Vector(list, 0);
    else Scm_Error("invalid unform vector tag: %s", tag);

    if (ctx->flags & SCM_READ_LITERAL_IMMUTABLE) {
        SCM_UVECTOR_IMMUTABLE_P(uv) = TRUE;
    }
    return uv;
}
