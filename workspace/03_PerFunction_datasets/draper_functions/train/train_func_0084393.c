write(hsStream* S) {
    if (!S->getVer().isMoul())
        S->writeInt(fI);
    fT.write(S);
    fQ.write(S);
    fU.write(S);
    fK.write(S);
    S->writeFloat(fF);
}
