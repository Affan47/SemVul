plCoordinateInterface() {
    fLocalToParent.Reset();
    fParentToLocal.Reset();
    fLocalToWorld.Reset();
    fWorldToLocal.Reset();

    fProps.setName(kDisable, "kDisable");
    fProps.setName(kCanEverDelayTransform, "kCanEverDelayTransform");
    fProps.setName(kDelayedTransformEval, "kDelayedTransformEval");
}
