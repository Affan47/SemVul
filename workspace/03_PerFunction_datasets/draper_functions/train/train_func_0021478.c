PrintGlobalVarRecord(void)
{
    RfmVar  var;
    char   *buf;

    BUFFER_CLEAR(buf);

    for (var = RFM_Global->var_list;
         var != NULL;
         var = var->next) {
        if (var->is_import) {
            buf += sprintf(buf, "   import ");
        } else {
            buf += sprintf(buf, "   ");
        }
#if 1
        if (var->is_static) {
            buf += sprintf(buf, "static ");
        }
#endif
        if (var->is_const) {
            buf += sprintf(buf, "const ");
        }
        if (var->is_restrict) {
            buf += sprintf(buf, "restrict ");
        }
        if (var->is_volatile) {
            buf += sprintf(buf, "volatile ");
        }
        buf = PrintRefAttr(buf, var->ref_type);
        buf += sprintf(buf, " V%d ", var->entry);
        buf = PrintVarName(buf, var);
        buf += sprintf(buf, " ??GBL;");
        NEW_LINE(buf);
    }
}
