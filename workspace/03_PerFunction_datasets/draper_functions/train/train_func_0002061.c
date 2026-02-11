GDALCloneTPSTransformer( void *hTransformArg )
{
    VALIDATE_POINTER1( hTransformArg, "GDALCloneTPSTransformer", NULL );

    TPSTransformInfo *psInfo =
        (TPSTransformInfo *) hTransformArg;


    CPLAtomicInc(&(psInfo->nRefCount));

    return psInfo;
}
