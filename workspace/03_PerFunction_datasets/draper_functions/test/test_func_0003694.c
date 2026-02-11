ensChainedassemblymapperTrace(const EnsPChainedassemblymapper cam,
                                     ajuint level)
{
    AjPStr indent = NULL;

    if (!cam)
        return ajFalse;

    indent = ajStrNew();

    ajStrAppendCountK(&indent, ' ', level * 2);

    ajDebug("%SensChainedassemblymapperTrace %p\n"
            "%S  Adaptor %p\n"
            "%S  CoordsystemSource %p\n"
            "%S  CoordsystemMiddle %p\n"
            "%S  CoordsystemTarget %p\n"
            "%S  MapperSourceMiddle %p\n"
            "%S  MapperTargetMiddle %p\n"
            "%S  MapperSourceTarget %p\n"
            "%S  RegistrySource %p\n"
            "%S  RegistryTarget %p\n"
            "%S  Maximum %u\n"
            "%S  Use %u\n",
            indent, cam,
            indent, cam->Adaptor,
            indent, cam->CoordsystemSource,
            indent, cam->CoordsystemMiddle,
            indent, cam->CoordsystemTarget,
            indent, cam->MapperSourceMiddle,
            indent, cam->MapperTargetMiddle,
            indent, cam->MapperSourceTarget,
            indent, cam->RegistrySource,
            indent, cam->RegistryTarget,
            indent, cam->Maximum,
            indent, cam->Use);

    ensCoordsystemTrace(cam->CoordsystemSource, level + 1);
    ensCoordsystemTrace(cam->CoordsystemMiddle, level + 1);
    ensCoordsystemTrace(cam->CoordsystemTarget, level + 1);

    ensMapperTrace(cam->MapperSourceMiddle, level +1);
    ensMapperTrace(cam->MapperTargetMiddle, level +1);
    ensMapperTrace(cam->MapperSourceTarget, level +1);

    ajStrDel(&indent);

    return ajTrue;
}
