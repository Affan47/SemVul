RemoveVoiceFromAllocedList(opl_voice_t *voice)
{
    opl_voice_t **rover;

    rover = &voice_alloced_list;


    while (*rover != NULL)
    {
        if (*rover == voice)
        {
            *rover = voice->next;
            voice->next = NULL;
            break;
        }

        rover = &(*rover)->next;
    }
}
