Scm_TreeCoreCheckConsistency(ScmTreeCore *tc)
{
    Node *r = ROOT(tc);
    int cnt = 0;

    if (!BLACKP(r)) Scm_Error("[internal] tree map root node is not black.");
    if (r) check_traverse(r, 1, &cnt);
    if (cnt != tc->num_entries) {
        Scm_Error("[internal] tree map node count mismatch: record %d vs actual %d", tc->num_entries, cnt);
    }
}
