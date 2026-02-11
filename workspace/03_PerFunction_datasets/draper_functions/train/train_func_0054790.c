parse_htpl_switch_rnd___rev(stack, untag)
    int untag;
    STR stack; {

    TOKEN token;
    static done = 0;
    STR buff;
    int code;
    static int nesting = 0;
    static int refcount = 0;

    refcount++;
    makepersist(stack);
    printcode("}; my @__htpl_case_keys = keys %__htpl_cases;\n");
    printcode("        my $__htpl_rcase = int(rand(@__htpl_case_keys));\n");
    printcode("	$__htpl_cases_choose = $__htpl_case_keys[$__htpl_rcase]; {\n");
    code = 1;
    kludge_reunifying = 1;
    asprintf(&buff, "SWITCH CASE");
    kludge_reunifying = 0;
    nest++;
    code = parse_htpl(buff, 1);
    nest--;
    if (!code) {
        croak("Unification of '%s' failed", buff);
        free(buff);
        RETURN(0)
    }
    free(buff);

    printcode("}\n");
    if (!currscope) RETURN(croak("Unexpected SWITCH RND"))
    if (currscope->scope != scope_random_switch) RETURN(croak("Now in scope %s from %d and met SWITCH RND, expecting: random-switch", scope_names[currscope->scope], currscope->nline))
    popscope();
    nesting = 0;
    RETURN(1)
}
