_dxf_ExInitPacket(void)
{
    tmpbufferlock = (lock_type *) DXAllocate (sizeof (lock_type));
    if (tmpbufferlock == NULL)
        return (ERROR);
    DXcreate_lock(tmpbufferlock, 0);

    tmpbuffer = (char **) DXAllocateZero(sizeof(char*));
    if(tmpbuffer == NULL)
        return ERROR;
    *tmpbuffer = NULL;
    tmpbuffersize = (int *) DXAllocateZero(sizeof(int));
    if(tmpbuffersize == NULL)
        return ERROR;
    tmpbufferused = (int *) DXAllocateZero(sizeof(int));
    if(tmpbufferused == NULL)
        return ERROR;
    return OK;
}
