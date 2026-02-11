createTransformTag (
        payload_t ** lastPayload_ptr,
        transform_t * transformList_ptr,
        INT64 * globalPayloadSize)
{
    int err = OK;
    transform_t * curTransform_ptr = transformList_ptr;
    payload_t * headerPayload_ptr;
    INT64 payloadSize = 0;


    if (transformList_ptr->next)
    {


        err = createPayload(&((*lastPayload_ptr)->next), 11, NULL);
        if (err != OK) return err;


        *lastPayload_ptr = (*lastPayload_ptr)->next;
        headerPayload_ptr = *lastPayload_ptr;

        while (curTransform_ptr)
        {
            err = createTransformBlock(
                    curTransform_ptr,
                    lastPayload_ptr,
                    &payloadSize);
            if (err != OK) return err;

            curTransform_ptr = curTransform_ptr->next;
        }


        headerPayload_ptr->data[0] = TRANSFORM_TABLE;
        headerPayload_ptr->cur_length = 1;


        encodeMBUINT(payloadSize, headerPayload_ptr);


        *globalPayloadSize += payloadSize + headerPayload_ptr->cur_length;

    } else {


        createTransformBlock(
                curTransform_ptr,
                lastPayload_ptr,
                globalPayloadSize);
    }
    return err;
}
