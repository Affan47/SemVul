id3v2_add_latin1(lame_t gfp, uint32_t frame_id, char const *lang, char const *desc, char const *text)
{
    lame_internal_flags *gfc = gfp != 0 ? gfp->internal_flags : 0;
    if (gfc != 0) {
        FrameDataNode *node = findNode(&gfc->tag_spec, frame_id, 0);
        if (isMultiFrame(frame_id)) {
            while (node) {
                if (isSameLang(node->lng, lang)) {
                    if (isSameDescriptor(node, desc)) {
                        break;
                    }
                }
                node = findNode(&gfc->tag_spec, frame_id, node);
            }
        }
        if (node == 0) {
            node = lame_calloc(FrameDataNode, 1);
            if (node == 0) {
                return -254;
            }
            appendNode(&gfc->tag_spec, node);
        }
        node->fid = frame_id;
        setLang(node->lng, lang);
        node->dsc.dim = local_strdup(&node->dsc.ptr.l, desc);
        node->dsc.enc = 0;
        node->txt.dim = local_strdup(&node->txt.ptr.l, text);
        node->txt.enc = 0;
        gfc->tag_spec.flags |= (CHANGED_FLAG | ADD_V2_FLAG);
        return 0;
    }
    return -255;
}
