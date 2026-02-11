main(int argc, const char *argv[])
{
    int i, argc_ = argc;
    const char *argv_[argc_];
    const char *fname = parse_option(&argc_, argv, argv_);
    if (fname == NULL) {
        fprintf(stderr, "%s [--emit-llvm/--emit-js] file\n", argv[0]);
        return 1;
    }
    konoha_t konoha = konoha_open();
    CTX ctx = konoha;
    kString *s = new_T(fname);
    knh_DictMap_set(ctx, ctx->share->props, new_T("script.name"), s);

    kArray *a = new_Array(ctx, CLASS_String, argc_);
    for(i = 2; i < argc_; i++) {
        knh_Array_add(ctx, a, new_String2(ctx, CLASS_String, argv_[i],
                    knh_strlen(argv_[i]), SPOL_TEXT|SPOL_POOLALWAYS));
    }
    knh_DictMap_set(ctx, ctx->share->props, new_T("script.argv"), a);

    kbytes_t t = knh_bytes_nsname(S_tobytes(s));
    knh_Script_setNSName(ctx, ctx->script, new_S(t.text, t.len));
    kbytes_t pkgname = STEXT("konoha.compiler");
    knh_loadPackage(ctx, pkgname);

    load_codegenerator(ctx);
    if (!compiler_run_main) {
        knh_setCompileMode(ctx, 1);
    }
    knh_startScript(ctx, (const char*)fname);


    kMethod *mtd = load_method(ctx,
            O_cid(ctx->share->konoha_compiler), STEXT("dump"));
    BEGIN_LOCAL(ctx, lsfp, K_CALLDELTA+1); {
        KNH_SETv(ctx, lsfp[K_CALLDELTA].o, ctx->share->konoha_compiler);
        KNH_SCALL(ctx, lsfp, 0, mtd, 0);
    } END_LOCAL(ctx, lsfp);
    if (compiler_run_main) {
        knh_stack_clear(ctx, ctx->stack);
        knh_runMain(ctx, argc_, argv_);
    }
    konoha_close(konoha);
    return 0;
}
