get_exit(int n) {
    for (int i = 0; i < n_exits; i++) {
        if (exits[i].num == n)
            return &exits[i];
    }
    return NULL;
}
