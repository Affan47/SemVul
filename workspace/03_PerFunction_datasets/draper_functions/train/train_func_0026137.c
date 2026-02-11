scm_make_value_packet(ScmObj values)
{
    ScmObj obj;

    obj = scm_alloc_cell();
    SCM_VALUEPACKET_INIT(obj, values);
    return obj;
}
