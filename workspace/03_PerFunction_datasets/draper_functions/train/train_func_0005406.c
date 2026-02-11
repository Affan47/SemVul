showClassHierarchy(int this, int depth)
{
    int i;
    int child;

    output("$i");
    for (i=0; i < depth; i++)
        output("$t");
    listClass(this);
    for (child = 1; child <= header->classMax; child++) {
        if (classes[child].parent == this) {
            showClassHierarchy(child, depth+1);
        }
    }
}
