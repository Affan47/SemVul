updateBounds() {

    user_bounds.reset();
    active_user_bounds.reset();

    for(std::map<std::string,RUser*>::iterator it = users.begin(); it!=users.end(); it++) {
        RUser* user = it->second;

        user->updateQuadItemBounds();
        user_bounds.update(user->quadItemBounds);

        if(!user->isIdle()) {
            active_user_bounds.update(user->quadItemBounds);
        }

    }

    dir_bounds.reset();

    for(std::map<std::string,RDirNode*>::iterator it = gGourceDirMap.begin(); it!=gGourceDirMap.end(); it++) {
        RDirNode* node = it->second;

        if(node->isVisible()) {
            node->updateQuadItemBounds();
            dir_bounds.update(node->quadItemBounds);
        }
    }
}
