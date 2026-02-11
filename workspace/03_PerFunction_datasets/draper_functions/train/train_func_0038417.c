ajTableMergeOr(AjPTable thys, AjPTable table)
{
    ajulong i = 0UL;

    AjBool ismatch = ajFalse;

    AjPTableNode p       = NULL;
    AjPTableNode q       = NULL;
    AjPTableNode tmpnode = NULL;
    AjPTableNode qprev   = NULL;
    AjPTableNode pfirst  = NULL;
    AjPTableNode qfirst  = NULL;
    AjPTableNode qtmp    = NULL;


    if(table->Size > thys->Size)
        ajTableResizeHashsize(thys, table->Size);
    else if(thys->Size > table->Size)
        ajTableResizeHashsize(table, thys->Size);


    for(i=0UL; i < thys->Size; i++)
    {
        pfirst = thys->Buckets[i];
        qfirst = table->Buckets[i];

        p = pfirst;

        while(p)
        {
            ismatch = ajFalse;

            qprev = NULL;
            for(q = qfirst; q; q = q->Link)
            {
                if((*thys->Fcmp)(p->Key, q->Key) == 0)
                {
                    ismatch = ajTrue;
                    break;
                }
                qprev = q;
            }

            p = p->Link;

            if(ismatch)
            {
                tmpnode = q->Link;

                if(table->Fkeydel)
                    (*table->Fkeydel)(&q->Key);
                if(table->Fvaldel)
                    (*table->Fvaldel)(&q->Value);

                if(tableFreeNext >= tableFreeMax)
                    tableFreeSetExpand();
                if(tableFreeNext >= tableFreeMax)
                    AJFREE(q);
                else
                    tableFreeSet[tableFreeNext++] = q;

                q = tmpnode;

                if(qprev)
                    qprev->Link = tmpnode;
                else
                    qfirst = table->Buckets[i] = tmpnode;

                --table->Length;
            }
        }

        for(q = table->Buckets[i]; q; q = qtmp)
        {
            qtmp = q->Link;
            tmpnode = thys->Buckets[i];
            thys->Buckets[i] = q;
            q->Link = tmpnode;

            --table->Length;
            ++thys->Length;
        }
        table->Buckets[i] = NULL;
    }

    return ajTrue;
}
