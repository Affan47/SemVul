search_member( ED4_extension *location, ED4_properties prop)


{
    ED4_index   current_index = 0,
        rel_pos,
        rel_size;

    ED4_base *current_member;

    if ( prop & ED4_P_HORIZONTAL ) {
        rel_pos = Y_POS; rel_size = HEIGHT;
    }
    else {
        rel_pos = X_POS; rel_size = WIDTH;
    }

    current_member = memberList[0];
    if (! current_member) {
        return ( -1 );
    }

    current_index = 0;
    while (current_member) {
        if ( location->position[rel_pos] <= (current_member->extension.position[rel_pos] + current_member->extension.size[rel_size])) {
            return ( current_index );
        }
        current_index++;
        current_member = memberList[current_index];
    }

    return ( no_of_members );
}
