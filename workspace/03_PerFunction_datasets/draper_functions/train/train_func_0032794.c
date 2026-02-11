getTIDX (decodeISF_t * pDecISF)
{
    int err = OK;
    INT64 value,
          i = 0;
    transform_t * pTransform = pDecISF->transforms;

    err = readMBUINT(pDecISF, &value);
    if (err == OK)
    {
        LOG(stdout,"TIDX=%lld\n",value);

        while ( pTransform && i < value )
        {
            i++;
            pTransform = pTransform->next;
        }
        if (pTransform)
            pDecISF->curTransform = pTransform;
    }
    return err;
}
