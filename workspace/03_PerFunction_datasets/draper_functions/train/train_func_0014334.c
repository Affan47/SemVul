_dxfSetEnumeratedMember(Group a, int b, Object c) {
    if (!a)
        return NULL;
    return (*(struct group_class **)a)->SetEnumeratedMember((Group)a,b,c);
}
