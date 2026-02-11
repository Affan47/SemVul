ensQcdasfeatureNewRef(EnsPQcdasfeature qcdasf)
{
    if (!qcdasf)
        return NULL;

    qcdasf->Use++;

    return qcdasf;
}
