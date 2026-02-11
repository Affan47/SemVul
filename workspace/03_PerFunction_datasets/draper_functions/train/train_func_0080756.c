testTrixel(uint64 id)
{
    SpatialMarkup mark;
    uint64 childID;
    uint64 tid;


    const struct SpatialIndex::QuadNode *indexNode = &index_->nodes_[id];


    mark = testNode(id);


    switch(mark){
    case fULL:
        tid = N(id).id_;

        saveTrixel(tid);

        return mark;
    case rEJECT:
        tid = N(id).id_;
        return mark;
    default:


        break;
    }


    {
        childID = indexNode->childID_[0];
        if ( childID != 0){

            tid = N(id).id_;
            childID = indexNode->childID_[0];  testTrixel(childID);
            childID = indexNode->childID_[1];  testTrixel(childID);
            childID = indexNode->childID_[2];  testTrixel(childID);
            childID = indexNode->childID_[3];  testTrixel(childID);
        } else {
            if (addlevel_){
                testPartial(addlevel_, N(id).id_, V(NV(0)), V(NV(1)), V(NV(2)), 0);
            } else {
                saveTrixel(N(id).id_);
            }
        }
    }


    return mark;
}
