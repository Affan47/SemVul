NewStreakBuf(int nDim)
{
    Stream s = NULL;

    s = (Stream)DXAllocateZero(sizeof(struct stream));
    if (! s)
	goto error;

    s->pArray  = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 1, nDim);
    s->tArray  = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 0);
    s->vArray  = DXNewArray(TYPE_FLOAT, CATEGORY_REAL, 1, nDim);

    if (s->pArray == NULL || s->vArray == NULL || s->tArray == NULL)
	goto error;

    s->arrayKnt = 0;

    s->points  = (float *)DXAllocate(nDim*STREAM_BUF_POINTS*sizeof(float));
    s->time    = (float *)DXAllocate(STREAM_BUF_POINTS*sizeof(float));
    s->vectors = (float *)DXAllocate(nDim*STREAM_BUF_POINTS*sizeof(float));
    if (s->points  == NULL || s->time == NULL || s->vectors == NULL)
	goto error;

    s->nDim     = nDim;
    s->bufKnt   = 0;

    return s;

error:
    DestroyStreakBuf(s);

    return NULL;
}
