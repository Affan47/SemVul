add_list_item(ScmObj orig, ScmObj item, int afterp)
{
    if (afterp) {
        return Scm_Append2(orig, SCM_LIST1(item));
    } else {
        return Scm_Cons(item, orig);
    }
}
