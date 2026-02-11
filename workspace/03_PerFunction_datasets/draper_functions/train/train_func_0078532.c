helix_pairs_changed_cb(AW_window *aww, AW_CL changed, AW_CL cl_cb_struct) {
    static bool recursion = false;

    if (!recursion) {
        AW_cb_struct *awcbs     = reinterpret_cast<AW_cb_struct*>(cl_cb_struct);
        AW_root      *aw_root   = aww->get_root();
        AW_awar      *awar_pair = aw_root->awar(helix_pair_awar(changed));
        char         *pairdef   = awar_pair->read_string();

        recursion = true;
        for (int i = 0; ; i += 3) {
            char left  = toupper(pairdef[i]); if (!left) break;
            char right = toupper(pairdef[i+1]); if (!right) break;

            pairdef[i]   = left;
            pairdef[i+1] = right;

            for (int j = 0; helix_awars[j].awar; j++) {
                if (j != changed) {
                    AW_awar *awar_pair2 = aw_root->awar(helix_pair_awar(j));
                    char    *pd2        = awar_pair2->read_string();
                    int      dst        = 0;
                    bool     modified   = false;

                    for (int k = 0; ; k += 3) {
                        char l = toupper(pd2[k]); if (!l) break;
                        char r = toupper(pd2[k+1]); if (!r) break;

                        if ((left == l && right == r) || (left == r && right == l)) {

                            modified = true;
                        }
                        else {
                            pd2[dst]   = l;
                            pd2[dst+1] = r;

                            dst += 3;
                        }
                        if (!pd2[k+2]) break;
                    }

                    if (modified) {
                        pd2[dst-1] = 0;
                        awar_pair2->write_string(pd2);
                    }

                    free(pd2);
                }
            }

            if (!pairdef[i+2]) break;
        }
        awar_pair->write_string(pairdef);
        recursion = false;

        awcbs->run_callback();

        free(pairdef);
    }
}
