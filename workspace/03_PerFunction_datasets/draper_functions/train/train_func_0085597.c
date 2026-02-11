getTransformTranslate (decodeISF_t * pDecISF)
{
    int err = OK;
    transform_t * pTransform;


    if (pDecISF->lastTransform != &(pDecISF->transforms) )
    {
        err = createTransform(&pTransform);
        if (err != OK)
            return err;
    } else {
        pTransform = *(pDecISF->lastTransform);
    }

    err = readFloat (pDecISF, &pTransform->m13);
    if (err != OK) return err;
    err = readFloat (pDecISF, &pTransform->m23);
    if (err != OK) return err;

    LOG(stdout,"(TRANSFORM_TRANSLATE) m13 = %f\n", pTransform->m13);
    LOG(stdout,"(TRANSFORM_TRANSLATE) m23 = %f\n", pTransform->m23);


    *(pDecISF->lastTransform) = pTransform;
    pDecISF->lastTransform = &(pTransform->next);

    return err;
}
