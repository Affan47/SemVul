getString(const AbstractNodePtr &node, String *result)
    {
        if(node->type != ANT_ATOM)
            return false;
        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();
        *result = atom->value;
        return true;
    }
