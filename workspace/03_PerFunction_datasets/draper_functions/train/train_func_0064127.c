embBtreeParseFieldSecond(const AjPStr readline, AjPRegexp regexp,
                              EmbPBtreeField field)
{
    AjPStr tmpfd = NULL;

    if(ajRegExec(regexp, readline))
    {
        if(field->freecount)
            tmpfd = field->freelist[--field->freecount];

        ajRegSubI(regexp, 1, &tmpfd);
        ajRegSubI(regexp, 1, &tmpfd);

        if(ajStrGetLen(tmpfd))
        {
            ajListstrPushAppend(field->data, tmpfd);
            ajDebug("++%S '%S'\n", field->name, tmpfd);
            tmpfd = NULL;
            if(field->freecount)
                tmpfd = field->freelist[--field->freecount];
        }

        ajRegSubI(regexp,2, &tmpfd);

        if(ajStrGetLen(tmpfd))
        {
            ajListstrPushAppend(field->data,tmpfd);
            ajDebug("++%S '%S'\n", field->name, tmpfd);
            tmpfd = NULL;
        }
    }

    ajStrDel(&tmpfd);

    return;
}
