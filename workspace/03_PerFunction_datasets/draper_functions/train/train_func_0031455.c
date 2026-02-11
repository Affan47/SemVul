ref()
{

    if (newNodes) {
        HashSet<Node*>::iterator it = newNodes->find(this);
        if (it != newNodes->end()) {
            newNodes->remove(it);
            ASSERT(!nodeExtraRefCounts || !nodeExtraRefCounts->contains(this));
            return;
        }
    }

    ASSERT(!newNodes || !newNodes->contains(this));

    if (!nodeExtraRefCounts)
        nodeExtraRefCounts = new HashCountedSet<Node*>;
    nodeExtraRefCounts->add(this);
}
