ReleaseALBuffers(ALCdevice *device)
{
    ALsizei i;
    for(i = 0;i < device->BufferMap.size;i++)
    {
        ALbuffer *temp = device->BufferMap.array[i].value;
        device->BufferMap.array[i].value = NULL;

        free(temp->data);

        FreeThunkEntry(temp->buffer);
        memset(temp, 0, sizeof(ALbuffer));
        free(temp);
    }
}
