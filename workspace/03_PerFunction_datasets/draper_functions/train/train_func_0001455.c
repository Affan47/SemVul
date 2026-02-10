createTestGroup(MprTestService *sp, MprTestDef *def, MprTestGroup *parent)
{
    MprTestGroup    *gp, *child;
    MprTestDef      **dp;
    MprTestCase     *tc;
    char            name[80];
    static int      counter = 0;

    mprAssert(sp);
    mprAssert(def);

    gp = mprAllocObj(MprTestGroup, manageTestGroup);
    if (gp == 0) {
        return 0;
    }
    gp->service = sp;
    if (parent) {
        gp->dispatcher = parent->dispatcher;
    } else {
        mprSprintf(name, sizeof(name), "Test-%d", counter++);
        gp->dispatcher = mprCreateDispatcher(name, 1);
    }

    gp->failures = mprCreateList(0, 0);
    if (gp->failures == 0) {
        return 0;
    }
    gp->cases = mprCreateList(0, MPR_LIST_STATIC_VALUES);
    if (gp->cases == 0) {
        return 0;
    }
    gp->groups = mprCreateList(0, 0);
    if (gp->groups == 0) {
        return 0;
    }
    gp->def = def;
    gp->name = sclone(def->name);
    gp->success = 1;

    for (tc = def->caseDefs; tc->proc; tc++) {
        if (mprAddItem(gp->cases, tc) < 0) {
            return 0;
        }
    }
    if (def->groupDefs) {
        for (dp = &def->groupDefs[0]; *dp && (*dp)->name; dp++) {
            child = createTestGroup(sp, *dp, gp);
            if (child == 0) {
                return 0;
            }
            if (mprAddItem(gp->groups, child) < 0) {
                return 0;
            }
            child->parent = gp;
            child->root = gp->parent;
        }
    }
    return gp;
}
