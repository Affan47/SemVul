alloc_tgtdefn(const tgtdefn_t *prototype)

{   tgtdefn_t *tgt;

#define DFLT_OR_PROTO(dflt, proto) \
        (prototype == NULL ? (dflt) : (proto))

    tgt = (tgtdefn_t*)malloc(sizeof(tgtdefn_t));

    tgt->ident = NULL;
    tgt->flags = DFLT_OR_PROTO(FLG_DEFAULTS, prototype->flags);

    tgt->dev = NULL;
    tgt->start = 0; tgt->length = -1;
    tgt->dir = NULL;
    tgt->fstype = DFLT_OR_PROTO(NULL, cm_strdup(prototype->fstype));
    tgt->mountoptions = DFLT_OR_PROTO(NULL, cm_strdup(prototype->mountoptions));
    tgt->fsckoptions = DFLT_OR_PROTO(NULL, cm_strdup(prototype->fsckoptions));
    tgt->loopdev = NULL;

    tgt->cipher = DFLT_OR_PROTO(cm_strdup(CM_DEFAULT_CIPHER),
                                cm_strdup(prototype->cipher));
    tgt->ivoffset = 0;

    tgt->key.format = DFLT_OR_PROTO(NULL, cm_strdup(prototype->key.format));
    tgt->key.filename = NULL;
    tgt->key.digestalg = DFLT_OR_PROTO(NULL, cm_strdup(prototype->key.digestalg));
    tgt->key.cipheralg = DFLT_OR_PROTO(NULL, cm_strdup(prototype->key.cipheralg));
    tgt->key.maxlen = DFLT_OR_PROTO(-1L, prototype->key.maxlen);
    tgt->key.retries = DFLT_OR_PROTO(1U, prototype->key.retries);

    tgt->nx = NULL;

#undef DFLT_OR_PROTO

    return tgt;
}
