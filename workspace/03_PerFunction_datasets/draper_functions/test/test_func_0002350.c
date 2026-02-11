getRC( MVT VT ) {
  switch( VT.SimpleTy ) {
  case MVT::i8:
    return CurDAG->getTargetConstant(SPU::R8CRegClass.getID(), MVT::i32);
    break;
  case MVT::i16:
    return CurDAG->getTargetConstant(SPU::R16CRegClass.getID(), MVT::i32);
    break;
  case MVT::i32:
    return CurDAG->getTargetConstant(SPU::R32CRegClass.getID(), MVT::i32);
    break;
  case MVT::f32:
    return CurDAG->getTargetConstant(SPU::R32FPRegClass.getID(), MVT::i32);
    break;
  case MVT::i64:
    return CurDAG->getTargetConstant(SPU::R64CRegClass.getID(), MVT::i32);
    break;
  case MVT::i128:
    return CurDAG->getTargetConstant(SPU::GPRCRegClass.getID(), MVT::i32);
    break;
  case MVT::v16i8:
  case MVT::v8i16:
  case MVT::v4i32:
  case MVT::v4f32:
  case MVT::v2i64:
  case MVT::v2f64:
    return CurDAG->getTargetConstant(SPU::VECREGRegClass.getID(), MVT::i32);
    break;
  default:
    assert( false && "add a new case here" );
  }
  return SDValue();
}
