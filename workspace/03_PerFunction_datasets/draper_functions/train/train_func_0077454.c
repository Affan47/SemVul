Replace(int i){
    if (i>=0 && i < blocks.Len()){
        if (i==0 || blocks(i)->value > blocks(Lower(i))->value)
            SwapUp(i);
        else
            SwapDown(i);

#ifdef MEM_DEB
        CheckHeap();
#endif
    }
}
