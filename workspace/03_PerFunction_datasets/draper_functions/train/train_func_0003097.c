createTransformBlock (
        transform_t * transform_ptr,
        payload_t ** lastPayload_ptr,
        INT64 * blockPayloadSize)
{
    int err = OK;
    payload_t * payload_ptr = NULL;


    err = createPayload(&((*lastPayload_ptr)->next), 25, NULL);
    if (err != OK) return err;

    *lastPayload_ptr = (*lastPayload_ptr)->next;
    payload_ptr = *lastPayload_ptr;

    if (transform_ptr->m13 == 0 && transform_ptr->m23 == 0)
    {

        if (transform_ptr->m11 == transform_ptr->m22)
        {

            payload_ptr->data[payload_ptr->cur_length++] = TRANSFORM_ISOTROPIC_SCALE;
            putFloat(transform_ptr->m11, payload_ptr);
        } else {

            payload_ptr->data[payload_ptr->cur_length++] = TRANSFORM_ANISOTROPIC_SCALE;
            putFloat(transform_ptr->m11, payload_ptr);
            putFloat(transform_ptr->m22, payload_ptr);
        }
    } else {

        if (transform_ptr->m12 == 0 && transform_ptr->m21 == 0)
        {

            if (transform_ptr->m11 == 0 && transform_ptr->m22 == 0)
            {

                payload_ptr->data[payload_ptr->cur_length++] = TRANSFORM_TRANSLATE;
                putFloat(transform_ptr->m13, payload_ptr);
                putFloat(transform_ptr->m23, payload_ptr);
            } else {

                payload_ptr->data[payload_ptr->cur_length++] = TRANSFORM_SCALE_AND_TRANSLATE;
                putFloat(transform_ptr->m11, payload_ptr);
                putFloat(transform_ptr->m22, payload_ptr);
                putFloat(transform_ptr->m13, payload_ptr);
                putFloat(transform_ptr->m23, payload_ptr);
            }
        } else {

            payload_ptr->data[payload_ptr->cur_length++] = TRANSFORM;
            putFloat(transform_ptr->m11, payload_ptr);
            putFloat(transform_ptr->m21, payload_ptr);
            putFloat(transform_ptr->m12, payload_ptr);
            putFloat(transform_ptr->m22, payload_ptr);
            putFloat(transform_ptr->m13, payload_ptr);
            putFloat(transform_ptr->m23, payload_ptr);
        }
    }


    *blockPayloadSize += payload_ptr->cur_length;

    return err;
}
