pilSofRemove(PilSetOfFrames *set, const char *category)
{

    PilDictNode *frame_node = pilDictLookup(set, category);

    if (frame_node) {
        deletePilFrame((PilFrame *)pilDictGetData(frame_node));
        pil_free((void *)pilDictGetKey(frame_node));
        pilDictErase(set, frame_node);
    }

    return;

}
