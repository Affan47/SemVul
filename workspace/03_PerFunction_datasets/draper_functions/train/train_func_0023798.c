setCursorTo(ED4_cursor *cursor, int seq_pos, bool unfold_groups, ED4_CursorJumpType jump_type)
{
    ED4_group_manager *group_manager_to_unfold = is_in_folded_group();

    if (unfold_groups) {
        bool unfolded = false;

        while (group_manager_to_unfold && unfold_groups) {
            ED4_base *base = group_manager_to_unfold->search_spec_child_rek(ED4_L_BRACKET);
            if (!base) break;
            ED4_bracket_terminal *bracket = base->to_bracket_terminal();
            group_manager_to_unfold->unfold_group(bracket->id);
            unfolded = true;
            group_manager_to_unfold = is_in_folded_group();
        }

        if (unfolded) ED4_ROOT->refresh_all_windows(1);
    }

    if (!group_manager_to_unfold) {
        ED4_terminal *terminal = search_spec_child_rek(ED4_L_SEQUENCE_STRING)->to_terminal();
        if (terminal) {
            if (seq_pos == -1) seq_pos = cursor->get_sequence_pos();
            cursor->set_to_terminal(ED4_ROOT->get_aww(), terminal, seq_pos, jump_type);
            return true;
        }
    }

    return false;
}
