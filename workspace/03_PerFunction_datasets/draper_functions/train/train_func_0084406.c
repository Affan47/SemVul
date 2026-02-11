move_member(ED4_index old_pos, ED4_index new_pos) {
    if (old_pos>=0 && old_pos<no_of_members && new_pos>=0 && new_pos<no_of_members) {
        if (new_pos!=old_pos) {
            ED4_base *moved_member = memberList[old_pos];

            shift_list(old_pos+1, -1);
            shift_list(new_pos, 1);

            memberList[new_pos] = moved_member;
            moved_member->index = new_pos;

            e4_assert(members_ok());
        }
        return ED4_R_OK;
    }

    return ED4_R_IMPOSSIBLE;
}
