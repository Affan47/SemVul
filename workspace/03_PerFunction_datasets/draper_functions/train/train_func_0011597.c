sound_copy(sound_type snd)
{
    sound_type sndcopy;
    falloc_sound(sndcopy, "sound_copy");
    *sndcopy = *snd;
    sndcopy->extra = NULL;
    snd_list_ref(snd->list);

    if (snd->table) snd->table->refcount++;
#ifdef GC_DEBUG
    if (sndcopy == sound_to_watch)
		printf("sndcopy->table %x\n", sndcopy->table);
#endif
    return sndcopy;
}
