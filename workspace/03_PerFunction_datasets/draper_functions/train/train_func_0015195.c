countStackFrames(Frame *last, int max_depth) {
    int depth = 0;

    do {
        for(; last->mb != NULL; last = last->prev, depth++)
            if(depth == max_depth)
                goto out;
    } while((last = last->prev)->prev != NULL);

out:
    return depth;
}
