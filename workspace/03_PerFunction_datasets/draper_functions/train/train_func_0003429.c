builtins_mdObject_GetAttributeTypes
(
  NSSCKMDObject *mdObject,
  NSSCKFWObject *fwObject,
  NSSCKMDSession *mdSession,
  NSSCKFWSession *fwSession,
  NSSCKMDToken *mdToken,
  NSSCKFWToken *fwToken,
  NSSCKMDInstance *mdInstance,
  NSSCKFWInstance *fwInstance,
  CK_ATTRIBUTE_TYPE_PTR typeArray,
  CK_ULONG ulCount
)
{
  builtinsInternalObject *io = (builtinsInternalObject *)mdObject->etc;
  CK_ULONG i;

  if( io->n != ulCount ) {
    return CKR_BUFFER_TOO_SMALL;
  }

  for( i = 0; i < io->n; i++ ) {
    typeArray[i] = io->types[i];
  }

  return CKR_OK;
}
