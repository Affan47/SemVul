chkType1AttributeExistance(
  DcmItem* dset,
  const DcmTagKey& key)
{
    OFBool found = OFTrue;
    if (!dset->tagExistsWithValue(key)) {
        DcmTag t(key);
        OFLOG_WARN(dcmpschkLogger, MSGe_missingAtt << OFendl
            << "   Affected attribute: " << t.getXTag()
            << " " << t.getTagName() << OFendl);
        found = OFFalse;
    }
    return found;
}
