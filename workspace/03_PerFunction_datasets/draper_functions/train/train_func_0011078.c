set_to_initial_value()
{
  switch (actualTc()->kind()) {
  case CORBA::tk_null:
  case CORBA::tk_void:
    ToDynAnyImpl(this)->setValid();
    break;

  case CORBA::tk_short:      insert_short(0);     break;
  case CORBA::tk_long:       insert_long(0);      break;
  case CORBA::tk_ushort:     insert_ushort(0);    break;
  case CORBA::tk_ulong:      insert_ulong(0);     break;
#ifndef NO_FLOAT
  case CORBA::tk_float:      insert_float(0.0);   break;
  case CORBA::tk_double:     insert_double(0.0);  break;
#endif
  case CORBA::tk_boolean:    insert_boolean(0);   break;
  case CORBA::tk_char:       insert_char(0);      break;
  case CORBA::tk_octet:      insert_octet(0);     break;
  case CORBA::tk_any:
    {
      CORBA::Any a;
      insert_any(a);
      break;
    }
  case CORBA::tk_TypeCode:   insert_typecode(CORBA::_tc_null);        break;
  case CORBA::tk_objref:     insert_reference(CORBA::Object::_nil()); break;
  case CORBA::tk_string:
    insert_string(_CORBA_String_helper::empty_string);
    break;
#ifdef HAS_LongLong
  case CORBA::tk_longlong:   insert_longlong(0);     break;
  case CORBA::tk_ulonglong:  insert_ulonglong(0);    break;
#endif
#ifdef HAS_LongDouble
  case CORBA::tk_longdouble: insert_longdouble(0.0); break;
#endif
  case CORBA::tk_wchar:      insert_wchar(0);        break;
  case CORBA::tk_wstring:
    insert_wstring(_CORBA_WString_helper::empty_wstring);
    break;
  default:

    OMNIORB_ASSERT(0);
  }
}
