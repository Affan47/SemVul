unicastSound(edict_t *ent, int soundIndex, float volume)
{
    int mask = MASK_ENTITY_CHANNEL;

    if (volume != 1.0)
        mask |= MASK_VOLUME;

    gi.WriteByte(svc_sound);
    gi.WriteByte((byte)mask);
    gi.WriteByte((byte)soundIndex);
    if (mask & MASK_VOLUME)
        gi.WriteByte((byte)(volume * 255));
    gi.WriteShort(((ent - g_edicts - 1) << 3) + CHAN_NO_PHS_ADD);
    gi.unicast (ent, true);
}
