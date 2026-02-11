PQueue_Node_combine(PQueue *pq,
                                        PQueue_Node *pqn){
    register gint i, count;
    register GPtrArray *combine;
    register PQueue_Node *npqn;
    if(!pqn->next){
        return pqn;
        }
    combine = g_ptr_array_new();
    for(count = 0; pqn; count++){
        g_ptr_array_add(combine, pqn);
        pqn->prev->next = NULL;
        pqn = pqn->next;
        }
    count--;
    for(i = 0; i < count; i+=2)
        combine->pdata[i] = PQueue_Node_order(pq, combine->pdata[i],
                                                  combine->pdata[i+1]);
    if(!(count&1))
        combine->pdata[i-2] = PQueue_Node_order(pq, combine->pdata[i-2],
                                                    combine->pdata[i]);
    for(i-=2; i>=2; i-=2)
        combine->pdata[i-2] = PQueue_Node_order(pq, combine->pdata[i-2],
                                                    combine->pdata[i]);
    npqn = combine->pdata[0];
    g_ptr_array_free(combine, TRUE);
    return npqn;
    }
