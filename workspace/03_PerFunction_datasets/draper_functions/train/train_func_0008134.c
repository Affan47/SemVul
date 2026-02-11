CompactTrieCheck(const CompactTrie *ct, ScmObj obj,
                      void (*checker)(Leaf*, ScmObj))
{
    if (ct->root == NULL) {
        if (ct->numEntries != 0) {
            Scm_Error("%S: ct->root is NULL but numEntries is %d",
                      obj, ct->numEntries);
        }
    } else {
        int num_leaves = check_rec(ct->root, 0, checker, obj);
        if (ct->numEntries != num_leaves) {
            Scm_Error("%S: # of leafs (%d) and numEntries (%d) don't agreee",
                      obj, num_leaves, ct->numEntries);
        }
    }
}
