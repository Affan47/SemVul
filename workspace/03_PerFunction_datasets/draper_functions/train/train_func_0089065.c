writeDataStructure(FILE *out)
{
    fprintf(out, "qt_resource_struct = %s\"", mPrefix);
    QStack<RCCFileInfo*> pending;

    if (!root)
        return false;


    pending.push(root);
    int offset = 1;
    while(!pending.isEmpty()) {
        RCCFileInfo *file = pending.pop();
        file->childOffset = offset;


        QList<RCCFileInfo*> children = file->children.values();
        qSort(children.begin(), children.end(), qt_rcc_compare_hash);


        for(int i = 0; i < children.size(); ++i) {
            RCCFileInfo *child = children.at(i);
            ++offset;
            if(child->flags & RCCFileInfo::Directory)
                pending.push(child);
        }
    }


    pending.push(root);
    root->writeDataInfo(out);
    while(!pending.isEmpty()) {
        RCCFileInfo *file = pending.pop();


        QList<RCCFileInfo*> children = file->children.values();
        qSort(children.begin(), children.end(), qt_rcc_compare_hash);


        for(int i = 0; i < children.size(); ++i) {
            RCCFileInfo *child = children.at(i);
            child->writeDataInfo(out);
            if(child->flags & RCCFileInfo::Directory)
                pending.push(child);
        }
    }
    fprintf(out, "\"\n");

    return true;
}
