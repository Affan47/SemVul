string_scan(ScmString *ss1, const char *s2,
                          int siz2, int len2, int incomplete2,
                          int retmode,
                          int (*searcher)(const char*, int, int,
                                          const char*, int, int, int*, int*))
{
    int bi, ci, incomplete;
    const ScmStringBody *sb = SCM_STRING_BODY(ss1);
    const char *s1 = SCM_STRING_BODY_START(sb);
    int siz1 = SCM_STRING_BODY_SIZE(sb);
    int len1 = SCM_STRING_BODY_LENGTH(sb);

    if (retmode < 0 || retmode > SCM_STRING_SCAN_BOTH) {
        Scm_Error("return mode out fo range: %d", retmode);
    }

    if (!searcher(s1, siz1, len1, s2, siz2, len2, &bi, &ci)) {
        if (retmode <= SCM_STRING_SCAN_AFTER) {
            return SCM_FALSE;
        } else {
            return Scm_Values2(SCM_FALSE, SCM_FALSE);
        }
    }

    incomplete =
        (SCM_STRING_BODY_INCOMPLETE_P(sb) || incomplete2)?
        SCM_STRING_INCOMPLETE : 0;

    switch (retmode) {
    case SCM_STRING_SCAN_INDEX:
        return Scm_MakeInteger(ci);
    case SCM_STRING_SCAN_BEFORE:
        return Scm_MakeString(s1, bi, ci, incomplete);
    case SCM_STRING_SCAN_AFTER:
        return Scm_MakeString(s1+bi+siz2, siz1-bi-siz2,
                              len1-ci-len2, incomplete);
    case SCM_STRING_SCAN_BEFORE2:
        return Scm_Values2(Scm_MakeString(s1, bi, ci, incomplete),
                           Scm_MakeString(s1+bi, siz1-bi, len1-ci, incomplete));
    case SCM_STRING_SCAN_AFTER2:
        return Scm_Values2(Scm_MakeString(s1, bi+siz2, ci+len2, incomplete),
                           Scm_MakeString(s1+bi+siz2, siz1-bi-siz2,
                                          len1-ci-len2, incomplete));
    case SCM_STRING_SCAN_BOTH:
        return Scm_Values2(Scm_MakeString(s1, bi, ci, incomplete),
                           Scm_MakeString(s1+bi+siz2, siz1-bi-siz2,
                                          len1-ci-len2, incomplete));
    }
}
