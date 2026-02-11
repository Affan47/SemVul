DIMSE_warn_str(T_ASC_Association *assoc)
{
    return OFString("DIMSE Warning: (") + assoc->params->DULparams.callingAPTitle
        + "," + assoc->params->DULparams.calledAPTitle + "): ";
}
