Scm_VMIsA(ScmObj obj, ScmClass *klass)
{
    ScmClass *k = Scm_ClassOf(obj);
    if (!SCM_FALSEP(k->redefined)) {
        void *data[2];
        data[0] = obj;
        data[1] = klass;
        Scm_VMPushCC(is_a_cc, data, 2);
        return instance_class_redefinition(obj, k);
    }
    return SCM_MAKE_BOOL(Scm_TypeP(obj, klass));
}
