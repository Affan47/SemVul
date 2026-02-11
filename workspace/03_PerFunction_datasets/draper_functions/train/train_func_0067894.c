calcRadius() {

    float total_file_area = file_area * visible_count;

    dir_area = total_file_area;


    for(std::list<RDirNode*>::iterator it = children.begin(); it != children.end(); it++) {
        RDirNode* node = (*it);

        dir_area += node->getArea();

    }

    this->dir_radius = std::max(1.0f, (float)sqrt(dir_area)) * gGourceDirPadding;


    this->parent_radius = std::max(1.0, sqrt(total_file_area) * gGourceDirPadding);
}
