Len(){
    int ret=0;
    tListItemBase* x=this;
    while (x){
        ret++;
        x = x->next;
    }
    return ret;
}
