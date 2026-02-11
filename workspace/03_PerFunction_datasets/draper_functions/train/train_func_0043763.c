detect_group_state(AP_tree *at, AWT_graphic_tree_group_state *state, AP_tree *skip_this_son) {
    if (!at) return;
    if (at->is_leaf) {
        if (at->gb_node && GB_read_flag(at->gb_node)) state->marked_outside_groups++;
        return;
    }

    if (at->gb_node) {
        AWT_graphic_tree_group_state sub_state;
        if (at->leftson != skip_this_son) detect_group_state(at->leftson, &sub_state, skip_this_son);
        if (at->rightson != skip_this_son) detect_group_state(at->rightson, &sub_state, skip_this_son);

        if (at->gr.grouped) {
            state->closed++;
            if (!sub_state.has_groups()) state->closed_terminal++;
            if (sub_state.marked()) state->closed_with_marked++;
            state->closed += sub_state.opened;
        }
        else {
            state->opened++;
            if (!sub_state.has_groups()) state->opened_terminal++;
            if (sub_state.marked()) state->opened_with_marked++;
            state->opened += sub_state.opened;
        }

        state->marked_in_groups += sub_state.marked();

        state->closed             += sub_state.closed;
        state->opened_terminal    += sub_state.opened_terminal;
        state->closed_terminal    += sub_state.closed_terminal;
        state->opened_with_marked += sub_state.opened_with_marked;
        state->closed_with_marked += sub_state.closed_with_marked;
    }
    else {
        if (at->leftson != skip_this_son) detect_group_state(at->leftson, state, skip_this_son);
        if (at->rightson != skip_this_son) detect_group_state(at->rightson, state, skip_this_son);
    }
}
