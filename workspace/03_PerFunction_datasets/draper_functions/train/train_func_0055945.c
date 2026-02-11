mprSetMimeProgram(MprHash *table, cchar *mimeType, cchar *program)
{
    MprKey      *kp;
    MprMime     *mt;

    kp = 0;
    mt = 0;
    while ((kp = mprGetNextKey(table, kp)) != 0) {
        mt = (MprMime*) kp->data;
        if (mt->type[0] == mimeType[0] && strcmp(mt->type, mimeType) == 0) {
            break;
        }
    }
    if (mt == 0) {
        mprError("Can't find mime type %s for action program %s", mimeType, program);
        return MPR_ERR_CANT_FIND;
    }
    mt->program = sclone(program);
    return 0;
}
