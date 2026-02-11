r_mark_DUr(struct SN_env * z) {
    {   int ret = r_check_vowel_harmony(z);
        if (ret == 0) return 0;
        if (ret < 0) return ret;
    }
    if (z->c - 2 <= z->lb || z->p[z->c - 1] != 114) return 0;
    if (!(find_among_b(z, a_18, 8))) return 0;
    return 1;
}
