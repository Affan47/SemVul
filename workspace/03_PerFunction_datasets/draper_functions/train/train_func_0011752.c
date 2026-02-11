ReleaseALSources(ALCcontext *Context)
{
    ALsizei pos;
    ALuint j;
    for(pos = 0;pos < Context->SourceMap.size;pos++)
    {
        ALsource *temp = Context->SourceMap.array[pos].value;
        Context->SourceMap.array[pos].value = NULL;


        while(temp->queue != NULL)
        {
            ALbufferlistitem *BufferList = temp->queue;
            temp->queue = BufferList->next;

            if(BufferList->buffer != NULL)
                DecrementRef(&BufferList->buffer->ref);
            free(BufferList);
        }

        for(j = 0;j < MAX_SENDS;++j)
        {
            if(temp->Send[j].Slot)
                DecrementRef(&temp->Send[j].Slot->ref);
            temp->Send[j].Slot = NULL;
        }


        FreeThunkEntry(temp->source);
        memset(temp, 0, sizeof(ALsource));
        free(temp);
    }
}
