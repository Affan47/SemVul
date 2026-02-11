updateFilesVBO(quadbuf& buffer, float dt) const{

    if(in_frustum) {

        for(std::list<RFile*>::const_iterator it = files.begin(); it!=files.end(); it++) {
            RFile* f = *it;

            if(f->isHidden()) continue;

            vec3 col   = f->getColour();
            float alpha = f->getAlpha();

            buffer.add(f->graphic->textureid, f->getAbsolutePos() - f->dims*0.5f, f->dims, vec4(col.x, col.y, col.z, alpha));
        }
    }

    for(std::list<RDirNode*>::const_iterator it = children.begin(); it != children.end(); it++) {
        RDirNode* node = (*it);
        node->updateFilesVBO(buffer,dt);
    }
}
