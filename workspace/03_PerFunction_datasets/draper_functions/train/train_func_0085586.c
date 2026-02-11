isLegalMaskedLoad(Type *DataTy) {
  Type *ScalarTy = DataTy->getScalarType();


  int DataWidth = ScalarTy->getPrimitiveSizeInBits();

  return (DataWidth >= 32 && ST->hasAVX2());
}
