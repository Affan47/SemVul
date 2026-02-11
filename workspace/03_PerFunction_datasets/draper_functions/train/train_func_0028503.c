set_fork_info(int entry_num, IntSet bvpt)
{
    int size;

    size = mts_num;

    if ((bvpt == NULL) && (size >= 0)) {
      construct_IntSet(bvpt,size+1);
    }

    if (entry_num > 0) {
        add1_IntSet(bvpt,entry_num);
    }

    return bvpt;
}
