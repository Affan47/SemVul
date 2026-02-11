get_first_terminal(int start_index) const {
    ED4_terminal *terminal = 0;

    if (children) {
        int i;
        for (i=start_index; !terminal && i>=0 && i<children->members(); i++) {
            ED4_base *base = children->member(i);
            if (base->is_terminal()) {
                terminal = base->to_terminal();
            }
            else {
                terminal = base->to_manager()->get_first_terminal();
            }
        }
    }

    return terminal;
}
