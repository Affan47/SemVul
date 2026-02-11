SetAttr(int attrCode,int val)
{
    switch (attrCode) {
    case TR_FID:
        attrSet.fid = val;
        break;
    case TR_SMC:
        attrSet.smc = val;
        break;
    case TR_STP:
        attrSet.stp = val;
        break;
    case TR_SWC:
        attrSet.swc = val;
        break;
    }

    return;
}
