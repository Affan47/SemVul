getPrevImplicit(UChar32 cp, collIterate *collationSource) {
    if(isNonChar(cp)) {
        return 0;
    }

    uint32_t r = uprv_uca_getImplicitPrimary(cp);

    *(collationSource->CEpos++) = (r & UCOL_PRIMARYMASK) | 0x00000505;
    collationSource->toReturn = collationSource->CEpos;

	if (collationSource->offsetBuffer == NULL) {
		collationSource->offsetBufferSize = UCOL_EXPAND_CE_BUFFER_SIZE;
		collationSource->offsetBuffer = (int32_t *) uprv_malloc(sizeof(int32_t) * UCOL_EXPAND_CE_BUFFER_SIZE);
		collationSource->offsetStore = collationSource->offsetBuffer;
	}


	if (collationSource->flags & UCOL_ITER_INNORMBUF) {
	  collationSource->offsetRepeatCount = 1;
	} else {
	  int32_t firstOffset = (int32_t)(collationSource->pos - collationSource->string);

	  *(collationSource->offsetStore++) = firstOffset;
	  *(collationSource->offsetStore++) = firstOffset + 1;

		collationSource->offsetReturn = collationSource->offsetStore - 1;
		*(collationSource->offsetBuffer) = firstOffset;
		if (collationSource->offsetReturn == collationSource->offsetBuffer) {
			collationSource->offsetStore = collationSource->offsetBuffer;
		}
	}

    return ((r & 0x0000FFFF)<<16) | 0x000000C0;
}
