getHimetricSize (decodeISF_t * pDecISF)
{
    int err = OK;
    ISF_t * pISF = pDecISF->ISF;
    INT64 endPayload,
          value;


    err = readMBUINT(pDecISF, &value);

    if (err == OK && value != 0)
    {
        LOG(stdout,"payload size = %lld\n", value);
        endPayload = pDecISF->bytesRead + value;

        err = readMBSINT (pDecISF, &value);
        if (err != OK) return err;
        pISF->width = value;
        err = readMBSINT (pDecISF, &value);
        if (err != OK) return err;
        pISF->height = value;
        LOG(stdout,"(HIMETRIC_SIZE) width=%lld, height=%lld\n",
                pISF->width,
                pISF->height);
        err = finishPayload(pDecISF,"(HIMETRIC_SIZE)",endPayload);
    }
    return err;
}
