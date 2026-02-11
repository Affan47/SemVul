_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if( omni::strMatch(op, "copy_relationship") ) {

    _0RL_cd_604b33dd2aae1b7f_71000000 _call_desc(_0RL_lcfn_604b33dd2aae1b7f_81000000, "copy_relationship", 18, 1);

    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "move_relationship") ) {

    _0RL_cd_604b33dd2aae1b7f_c0000000 _call_desc(_0RL_lcfn_604b33dd2aae1b7f_91000000, "move_relationship", 18, 1);

    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "life_cycle_propagation") ) {

    _0RL_cd_604b33dd2aae1b7f_a1000000 _call_desc(_0RL_lcfn_604b33dd2aae1b7f_b1000000, "life_cycle_propagation", 23, 1);

    _handle.upcall(this,_call_desc);
    return 1;
  }


#ifndef _MSC_VER
  if( CosRelationships__impl_Relationship::_dispatch(_handle) ) {
    return 1;
  }
#else

  if( ((CosRelationships__impl_Relationship*)this)->
      CosRelationships__impl_Relationship::_dispatch(_handle) ) {
    return 1;
  }
#endif


  return 0;
}
