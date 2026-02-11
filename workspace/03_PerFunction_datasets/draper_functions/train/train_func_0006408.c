PQueue_pop(PQueue *pq){
    register PQueue_Node *pqn = pq->root;
    register gpointer data;
    if(!pq->root)
        return NULL;
    data = pq->root->data;
    g_assert((pq->total <= 1) || pq->root->left);
    pq->root = pq->root->left
             ? PQueue_Node_combine(pq, pq->root->left)
             : NULL;
    g_assert(pqn);
    RecycleBin_recycle(pq->set->node_recycle, pqn);
    if(!--pq->total)
        pq->root = NULL;
    return data;
    }
