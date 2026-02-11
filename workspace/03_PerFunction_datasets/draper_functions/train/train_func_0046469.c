WriteEndTrack(MEMFILE *midioutput)
{
    byte endtrack[] = {0xFF, 0x2F, 0x00};

    if (WriteTime(queuedtime, midioutput))
    {
        return true;
    }

    if (mem_fwrite(endtrack, 1, 3, midioutput) != 3)
    {
        return true;
    }

    tracksize += 3;
    return false;
}
