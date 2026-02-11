check_loop_const_top(Block *loop, int entry){
    Boolean check_const = FALSE;

    if (get_loop_index_operand(loop)->entry == entry){
        check_const = check_loop_const(loop);
    }
    else if (loop->inner != NULL && check_const == FALSE){
        check_const = check_loop_const_inner(loop->inner, entry);
    }

    return check_const;
}
