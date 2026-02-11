btreeSecbucketNew(ajuint n, ajuint idlen)
{
    AjPSecbucket bucket = NULL;
    ajuint i;


    if(n)
    {
        if(statSaveSecbucketNext)
        {
            bucket = statSaveSecbucket[--statSaveSecbucketNext];
            for(i=0;i<bucket->Maxentries;++i)
                MAJSTRASSIGNCLEAR(&bucket->SecIds[i]);
            if(n > bucket->Maxentries)
            {
                AJCRESIZE0(bucket->keylen,bucket->Maxentries,n);
                AJCRESIZE0(bucket->SecIds,bucket->Maxentries,n);
                for(i=bucket->Maxentries;i<n;++i)
                    bucket->SecIds[i] = ajStrNewRes(idlen+1);
                bucket->Maxentries = n;
            }

        }
        else
        {
            AJNEW0(bucket);

            AJCNEW0(bucket->SecIds,n);
            AJCNEW0(bucket->keylen,n);
            for(i=0;i<n;++i)
                bucket->SecIds[i] = ajStrNewRes(idlen+1);
            bucket->Maxentries = n;
        }
    }
    else
    {
        if(statSaveSecbucketEmptyNext)
            bucket = statSaveSecbucketEmpty[--statSaveSecbucketEmptyNext];
        else
            AJNEW0(bucket);
    }

    bucket->NodeType = BT_SECBUCKET;
    bucket->Nentries = n;
    bucket->Overflow = 0UL;

    return bucket;
}
