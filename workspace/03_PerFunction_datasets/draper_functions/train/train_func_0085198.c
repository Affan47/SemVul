Port(int i){
    if (i>=0 && i <num_viewports)
        return viewports[i];
    else
        return NULL;
}
