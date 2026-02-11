insert(AP_tree *new_brother) {
    AP_tree  *new_tree = dup();
    AP_FLOAT  laenge;

    new_tree->leftson  = this;
    new_tree->rightson = new_brother;
    new_tree->father   = new_brother->father;
    father             = new_tree;

    if (new_brother->father) {
        if (new_brother->father->leftson == new_brother) {
            laenge = new_brother->father->leftlen = new_brother->father->leftlen*.5;
            new_brother->father->leftson = new_tree;
        }
        else {
            laenge = new_brother->father->rightlen = new_brother->father->rightlen*.5;
            new_brother->father->rightson = new_tree;
        }
    }
    else {
        laenge = 0.5;
    }
    new_tree->leftlen   = laenge;
    new_tree->rightlen  = laenge;
    new_brother->father = new_tree;

    if (!new_tree->father) {
        tree_root->inform_about_changed_root(new_brother,new_tree);
    }
}
