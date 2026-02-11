save(ofstream & fp) const
    {
        uint wr = WT_NODE_INTERNAL_HDR;
        saveValue(fp,wr);
        bitmap->save(fp);
        if(left_child!=NULL) {
            left_child->save(fp);
        }
        else {
            wr = WT_NODE_NULL_HDR;
            saveValue(fp,wr);
        }
        if(right_child!=NULL) {
            right_child->save(fp);
        }
        else {
            wr = WT_NODE_NULL_HDR;
            saveValue(fp,wr);
        }
    }
