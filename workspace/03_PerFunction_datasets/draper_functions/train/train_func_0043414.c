remove_node(CdlLoadable owner, CdlContainer parent, CdlNode node)
{
    CYG_REPORT_FUNCNAME("CdlToplevel::remove_node");
    CYG_REPORT_FUNCARG3XV(owner, parent, node);
    CYG_PRECONDITION_CLASSC(node);
    CYG_PRECONDITION_ZERO_OR_CLASSC(owner);
    CYG_PRECONDITION_ZERO_OR_CLASSC(parent);
    CYG_PRECONDITIONC(node->owner  == owner);
    CYG_PRECONDITIONC(node->parent == parent);
    CYG_PRECONDITIONC(0 == node->toplevel);

    if (0 != owner) {
        node->owner = 0;
        owner->owned.erase(std::find(owner->owned.begin(), owner->owned.end(), node));
    }
    if (0 != parent) {
        node->parent = 0;
        parent->contents.erase(std::find(parent->contents.begin(), parent->contents.end(), node));
    }

    CYG_REPORT_RETURN();
}
