reproduce(int ind_level) {
    for (int i = 0; i < (int) lst.size(); i++) {
        ast_id* id = lst[i];
        id->reproduce(0);
        if (i != (int) (lst.size() - 1)) Out.push(", ");
    }
}
