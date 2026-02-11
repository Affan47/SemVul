process()
    {
        if(!limb || limb->index > 255 || !skin || !skin->geom || indexes.length() != weights.length()) return;
        geomnode *g = skin->geom;
        if(g->blends.empty()) loopi(g->numverts) g->blends.add();
        loopv(indexes)
        {
            int idx = indexes[i];
            double weight = weights[i];
            g->blends[idx].addweight(weight, limb->index);
        }
    }
